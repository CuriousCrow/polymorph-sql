#include "sqlitetable.h"
#include <QStringList>
#include <QSqlRecord>
#include <QSqlField>

#include "objects/appconst.h"
#include "utils/sqlqueryhelper.h"

#include <QDebug>

SqliteTableItem::SqliteTableItem()
  : DBTableItem()
{
  _constraintsModel = new VariantMapTableModel();
  _constraintsModel->registerColumn(F_TYPE, tr("Type"));
  _constraintsModel->registerColumn(F_NAME, tr("Name"));
  registerDependantObject(_constraintsModel);
}

SqliteTableItem::~SqliteTableItem()
{
}

void SqliteTableItem::reloadColumnsModel()
{
  _columnsModel->clear();
  QSqlRecord sqlColumns = SqlQueryHelper::tableRowInfo(
        this->caption(),
        connectionName());
  for (int i=0; i<sqlColumns.count(); i++) {
    QSqlField field = sqlColumns.field(i);
    QString colType = NoType;
    switch (field.typeID()) {
    case QMetaType::QString:
      colType = "TEXT";
      break;
    case QMetaType::Int:
      colType = "INTEGER";
      break;
    case QMetaType::Double:
      colType = "REAL";
      break;
    default:
      break;
    }
    SqlColumn col(field.name(), colType);
    col.setDefaultValue(field.defaultValue());
    col.setIsPrimary(field.isAutoValue());
    col.setLength(field.length());
    col.setPrecision(field.precision());
    col.setNotNull(field.requiredStatus());
    col.setAutoIncrement(field.isAutoValue());
    _columnsModel->addSqlColumn(col, true);
  }
}

void SqliteTableItem::reloadConstraintsModel()
{
  //New table (not yet commited)
  if (connectionName().isEmpty())
    return;
  _constraintsModel->clear();
  QString sql =
      "select sql \"name\" from sqlite_master\n"
      "where type = 'table' and name = '#caption#'";
  QString preparedSql = fillSqlPatternWithFields(sql);
  QSqlQuery query = SqlQueryHelper::execSql(preparedSql, connectionName());
  int fakeId = 1;
  if (query.next()) {
    QString sql = query.value(F_NAME).toString();

    sql = sql.section('(', 1);
    QStringList words = sql.split(' ', Qt::SkipEmptyParts);
    int pkIdx = words.indexOf("PRIMARY");
    if (pkIdx >= 2) {
      QVariantMap item;
      item.insert(F_ID, fakeId);
      item.insert(F_NAME, words.at(pkIdx - 2));
      item.insert(F_TYPE, "PRIMARY KEY");
      _constraintsModel->addRow(item);
    }
  }
}

ActionResult SqliteTableItem::insertMe()
{
  return execSql(toDDL(), connectionName());
}

ActionResult SqliteTableItem::updateMe()
{
  qDebug() << "QDBSqliteTableItem::updateMe()";
  ActionResult res = DBTableItem::updateMe();
  if (res.isSuccess())
    return res;

  //Create new table
  QString sql = createTableQuery("tempTable");
  SqlQueryHelper::execSql(sql, connectionName());

  //Move remained columns into new table
  QHash<QString, QString> colNames = _columnsModel->permanentColNames();
  QStringList oldNames;
  QStringList newNames;
  QStringList keys = colNames.keys();
  QHashIterator<QString, QString> i(colNames);
  while(i.hasNext()) {
      i.next();
      oldNames.append(i.key());
      newNames.append(i.value());
  }
  sql = "INSERT INTO tempTable (%1) SELECT %2 FROM #caption.old#";
  QString preparedSql = fillSqlPatternWithFields(sql).arg(newNames.join(", "), oldNames.join(", "));
  res = execSql(preparedSql, connectionName());
  if (!res.isSuccess())
    return res;

  sql = "DROP TABLE #caption.old#";
  preparedSql = fillSqlPatternWithFields(sql);
  res = execSql(preparedSql, connectionName());
  if (!res.isSuccess())
    return res;

  //Rename temporary table back
  sql = "ALTER TABLE tempTable RENAME TO #caption.new#";
  preparedSql = fillSqlPatternWithFields(sql);
  res = execSql(preparedSql, connectionName());
  if (!res.isSuccess())
    return res;

  return RES_OK_CODE;
}

QString SqliteTableItem::createTableQuery(QString table) const
{
  QString createPattern = "CREATE TABLE %1 (%2);";
  QStringList pkColList;
  QStringList colDefList;
  bool rowIdPk = _columnsModel->hasOneColumnPK();
  for(int i=0; i<_columnsModel->rowCount(); i++) {
    SqlColumn col = _columnsModel->columnByIndex(i);
    if (!rowIdPk && col.isPrimary())
      pkColList.append(col.name());
    QString colDef = col.name() + " " + col.type();
    if (rowIdPk && col.isPrimary()) {
      colDef.append(" PRIMARY KEY");
      if (col.autoIncrement())
        colDef.append(" AUTOINCREMENT");
    }
    if (col.notNull())
      colDef = colDef.append(" NOT NULL");
    if (!col.defaultValue().isNull())
      colDef = colDef.append(" DEFAULT ").append(col.defaultValue().toString());
    colDefList.append(colDef);
  }
  if (!pkColList.isEmpty()) {
    QString pkTemplate = "CONSTRAINT pk_#caption.new# PRIMARY KEY (%1)";
    colDefList.append(fillSqlPatternWithFields(pkTemplate).arg(pkColList.join(",")));
  }
  QString preparedSql = createPattern.arg(table, colDefList.join(", "));
  return preparedSql;
}


QString SqliteTableItem::toDDL() const
{
  return createTableQuery(caption());
}
