#include "qdbpostgrestableitem.h"
#include <QSqlQuery>
#include <QDebug>
#include "qsqlqueryhelper.h"
#include "../../models/sqlcolumnmodel.h"

QDBPostgresTableItem::QDBPostgresTableItem(QString caption, QObject *parent)
  : QDBTableItem(caption, parent)
{
  _columnsModel = new SqlColumnModel();
}

QDBPostgresTableItem::~QDBPostgresTableItem()
{
  delete _columnsModel;
}

ActionResult QDBPostgresTableItem::insertMe()
{
  return execSql(createTableQuery(caption()), connectionName());
}

ActionResult QDBPostgresTableItem::updateMe()
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

  res = QDBTableItem::updateMe();
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

void QDBPostgresTableItem::reloadColumnsModel()
{
  //Новая, еще не вставленная таблица
  if (connectionName().isEmpty())
    return;
  _columnsModel->clear();
  QString sql = "select t.column_name, t.data_type, t.is_nullable, t.column_default, t.character_maximum_length, t.numeric_precision, t.numeric_scale, c.constraint_type from INFORMATION_SCHEMA.columns t "
                "LEFT JOIN information_schema.key_column_usage u ON t.table_name = u.table_name AND t.column_name = u.column_name AND t.table_catalog = u.table_catalog "
                "LEFT JOIN INFORMATION_SCHEMA.table_constraints c ON c.constraint_name = u.constraint_name AND u.table_catalog = c.table_catalog "
                "WHERE t.table_catalog='#databaseName#' AND t.table_name='#caption#'";
  QString preparedSql = fillPatternWithFields(sql);
  QSqlQuery query = QSqlQueryHelper::execSql(preparedSql, connectionName());
  while (query.next()) {
    SqlColumn col(query.value("column_name").toString(), colTypeFromString(query.value("data_type").toString()));
    col.setDefaultValue(query.value("column_default"));
    col.setIsPrimary(query.value("constraint_type").toString() == "PRIMARY KEY");
    col.setLength(query.value("character_maximum_length").toInt());
    col.setPrecision(query.value("numeric_precision").toInt());
    col.setNotNull(query.value("is_nullable").toString() == "NO");
    _columnsModel->addSqlColumn(col, true);
  }
}

QString QDBPostgresTableItem::caption()
{
  return "\"" + fieldValue("caption").toString() + "\"";
}

QString QDBPostgresTableItem::createTableQuery(QString table)
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

QString QDBPostgresTableItem::columnDef(const SqlColumn &col)
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

QString QDBPostgresTableItem::typeDef(const SqlColumn &col)
{
  return _columnsModel->columnTypeCaption(col.type());
}

QString QDBPostgresTableItem::defaultDef(const SqlColumn &col)
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
