#include "postgrestable.h"
#include <QSqlQuery>
#include <QDebug>
#include "qsqlqueryhelper.h"
#include "../../models/sqlcolumnmodel.h"
#include "../appconst.h"
#include "postgresprimarykey.h"
#include "postgresforeignkey.h"
#include "postgresuniqueconstraint.h"
#include "postgrescheckconstraint.h"

PostgresTable::PostgresTable(QString caption, QObject *parent)
  : DBTableItem(caption, parent)
{
  _columnsModel = new SqlColumnModel();

  _constraintsModel = new VariantMapTableModel();
  _constraintsModel->registerColumn(F_TYPE, tr("Type"));
  _constraintsModel->registerColumn(F_NAME, tr("Name"));
}

PostgresTable::~PostgresTable()
{
  delete _columnsModel;
  delete _constraintsModel;
}

DBForeignKey *PostgresTable::newForeignKey()
{
  return new PostgresForeignKey("fk_" + fieldValue(F_CAPTION).toString());
}

DBPrimaryKey *PostgresTable::newPrimaryKey()
{
  return new PostgresPrimaryKey("pk_" + fieldValue(F_CAPTION).toString());
}

DBUniqueConstraint *PostgresTable::newUniqueConstraint()
{
  return new PostgresUniqueConstraint("uq_" + fieldValue(F_CAPTION).toString());
}

DBCheckConstraint *PostgresTable::newCheckConstraint()
{
  return new PostgresCheckConstraint("chk_" + fieldValue(F_CAPTION).toString());
}

ActionResult PostgresTable::insertMe()
{
  return execSql(createTableQuery(caption()), connectionName());
}

ActionResult PostgresTable::updateMe()
{
  qDebug() << "QDBPostgreqlTableItem::updateMe()";
  ActionResult res;

  //Переименование таблицы
  //TODO: Сделать отдельный виртуальный метод renameMe для всех объектов
  if (fieldModified("caption")) {
    qDebug() << "Rename table";
    QString sql = "ALTER TABLE \"#caption.old#\" RENAME TO \"#caption.new#\"";
    QString preparedSql = fillPatternWithFields(sql);
    res = execSql(preparedSql, connectionName());
    if (!res.isSuccess())
      return res;
  }

  res = DBTableItem::updateMe();
  if (res.isSuccess())
    return ActionResult();

  QHash<SqlColumn, SqlColumn> changes = _columnsModel->columnChanges();
  qDebug() << "Changes size:" << changes.count();
  foreach (SqlColumn fromCol, changes.keys()) {
    SqlColumn toCol = changes[fromCol];
    //    qDebug() << "Changes:" << fromCol << toCol;
    if (fromCol.type() == NoType) {
      //Добавление колонки
      qDebug() << "Add col:" << toCol;
      QString sql = "ALTER TABLE \"#caption.new#\" ADD COLUMN %1";
      QString colDef = columnDef(toCol);
      QString preparedSql = fillPatternWithFields(sql).arg(colDef);
      res = execSql(preparedSql, connectionName());
      if (!res.isSuccess())
        return res;
    }
    else if (toCol.type() == NoType) {
      //Удаление колонки
      qDebug() << "Drop col:" << fromCol;
      QString sql = "ALTER TABLE \"#caption.new#\" DROP COLUMN %1";
      QString preparedSql = fillPatternWithFields(sql).arg(fromCol.name());
      res = execSql(preparedSql, connectionName());
      if (!res.isSuccess())
        return res;
    }
    else {
      //Изменения колонки
      qDebug() << "Col modify:" << fromCol << "to" << toCol;
      QStringList difs;
      QString pattern;
      if (fromCol.type() != toCol.type() || fromCol.length() != toCol.length()) {
        pattern = "ALTER COLUMN %1 TYPE %2";
        difs.append(pattern.arg(toCol.name()).arg(typeDef(toCol)));
      }
      if (fromCol.defaultValue() != toCol.defaultValue()) {
        if (toCol.defaultValue().toString().isEmpty())
          pattern = "ALTER COLUMN %1 DROP DEFAULT %2";
        else {
          pattern = "ALTER COLUMN %1 SET DEFAULT %2";
        }
        difs.append(pattern.arg(toCol.name()).arg(toCol.defaultValue().toString()));
      }
      if (fromCol.notNull() != toCol.notNull()) {
        pattern = "ALTER COLUMN %1 ";
        pattern.append(toCol.notNull() ? "SET NOT NULL" : "DROP NOT NULL");
        difs.append(pattern.arg(toCol.name()));
      }
      if (fromCol.name() != toCol.name()) {
        pattern = "RENAME COLUMN \"%1\" TO \"%2\"";
        difs.append(pattern.arg(fromCol.name()).arg(toCol.name()));
      }
      if (difs.isEmpty()) {
        qWarning() << "Column unchanged case! Ignore column.";
        continue;
      }

      QString sql = "ALTER TABLE \"#caption.new#\" " + difs.join(",\n");
      QString preparedSql = fillPatternWithFields(sql);
      res = execSql(preparedSql, connectionName());
      if (!res.isSuccess())
        return res;
    }
  }
  return res;
}

void PostgresTable::reloadColumnsModel()
{
  //Новая, еще не вставленная таблица
  if (connectionName().isEmpty())
    return;
  _columnsModel->clear();
  QString sql =
      "select t.column_name, t.data_type, t.is_nullable, t.column_default, t.character_maximum_length, "
      "t.numeric_precision, t.numeric_scale, (pk.constraint_name is not null) primary_key "
      "from INFORMATION_SCHEMA.columns t "
      "left join "
      "(select tc.constraint_name, cu.column_name "
      "from INFORMATION_SCHEMA.table_constraints tc "
      "left join information_schema.key_column_usage cu on tc.constraint_name=cu.constraint_name "
      "where tc.table_name='person' and tc.constraint_type='PRIMARY KEY') as pk on t.column_name=pk.column_name "
      "WHERE t.table_catalog='#databaseName#' AND t.table_name='#caption#'";
  QString preparedSql = fillPatternWithFields(sql);
  QSqlQuery query = QSqlQueryHelper::execSql(preparedSql, connectionName());
  while (query.next()) {
    SqlColumn col(query.value("column_name").toString(), colTypeFromString(query.value("data_type").toString()));
    col.setDefaultValue(query.value("column_default"));
    col.setIsPrimary(query.value("primary_key").toBool());
    col.setLength(query.value("character_maximum_length").toInt());
    col.setPrecision(query.value("numeric_precision").toInt());
    col.setNotNull(query.value("is_nullable").toString() == "NO");
    _columnsModel->addSqlColumn(col, true);
  }
}


void PostgresTable::reloadConstraintsModel()
{
  //Новая, еще не вставленная таблица
  if (connectionName().isEmpty())
    return;
  _constraintsModel->clear();
  QString sql =
      "select distinct c2.constraint_name \"name\", c2.constraint_type \"type\"\n"
      "from INFORMATION_SCHEMA.table_constraints c2\n"
      "left join information_schema.key_column_usage c1 on c2.constraint_name=c1.constraint_name\n"
      "where c2.table_name='#caption#' and c2.constraint_name not like '%_not_null'\n";
  QString preparedSql = fillPatternWithFields(sql);
  QSqlQuery query = QSqlQueryHelper::execSql(preparedSql, connectionName());
  int fakeId = 1;
  while (query.next()) {
    QVariantMap item;
    item.insert(F_ID, fakeId++);
    item.insert(F_NAME, query.value(F_NAME));
    item.insert(F_TYPE, query.value(F_TYPE));
    _constraintsModel->addRow(item);
  }

}

QString PostgresTable::caption()
{
  return "\"" + fieldValue("caption").toString() + "\"";
}

QString PostgresTable::createTableQuery(QString table)
{
  QString createPattern = "CREATE TABLE %1 (%2);";
  QStringList pkColList;
  QStringList colDefList;
  for(int i=0; i<_columnsModel->rowCount(); i++) {
    SqlColumn col = _columnsModel->columnByIndex(i);
    if (col.isPrimary())
      pkColList.append(col.name());
    QString colDef = columnDef(col);
    colDefList.append(colDef);
  }
  if (!pkColList.isEmpty()) {
    QString pkTemplate = "CONSTRAINT pk_#caption.new# PRIMARY KEY (%1)";
    colDefList.append(fillPatternWithFields(pkTemplate).arg(pkColList.join(",")));
  }
  QString preparedSql = createPattern.arg(table).arg(colDefList.join(", "));
  return preparedSql;
}

QString PostgresTable::columnDef(const SqlColumn &col)
{
  QString colDef = col.name() + " " + _columnsModel->columnTypeCaption(col.type());
  if (col.length() > 0)
    colDef.append("(" + QString::number(col.length()) + ")");
  if (col.notNull())
    colDef = colDef.append(" NOT NULL");
  if (!col.defaultValue().isNull())
    colDef = colDef.append(" DEFAULT ").append(col.defaultValue().toString());
  return colDef;
}

QString PostgresTable::typeDef(const SqlColumn &col)
{
  return _columnsModel->columnTypeCaption(col.type());
}

QString PostgresTable::defaultDef(const SqlColumn &col)
{
  if (col.defaultValue().isNull())
    return "";

//  switch (col.type()) {
//  case ColumnType::BigInt:
//  case ColumnType::Integer:
//  case ColumnType::SmallInt:
//    return col.defaultValue().toString();
//  case ColumnType::Varchar:
//    return "'" + col.defaultValue().toString() + "'";
//  case ColumnType::Date:
//    return "'" + col.defaultValue().toString() + "'";
//  case ColumnType::Time:
//    return "'" + col.defaultValue().toString() + "'";
//  default:
    return "";
//  }
}