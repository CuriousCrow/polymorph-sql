#include "mysqltable.h"
#include "utils/sqlqueryhelper.h"
#include <QDebug>
#include "objects/appurl.h"
#include "objects/appconst.h"

MysqlTableItem::MysqlTableItem()
  : DBTableItem()
{
  _constraintsModel = new VariantMapTableModel();
  _constraintsModel->registerColumn(F_TYPE, tr("Type"));
  _constraintsModel->registerColumn(F_NAME, tr("Name"));
}

MysqlTableItem::~MysqlTableItem()
{
  delete _columnsModel;
}

ActionResult MysqlTableItem::insertMe()
{
  ActionResult result = execSql(createTableQuery(fieldValue(F_CAPTION).toString()), connectionName());
  if (result.isSuccess())
    submit();
  return result;
}

ActionResult MysqlTableItem::updateMe()
{
  qDebug() << "QDBMysqlTableItem::updateMe()";
  if (DBTableItem::updateMe().isSuccess())
    return RES_OK_CODE;

  ActionResult result;
  QHash<SqlColumn, SqlColumn> changes = _columnsModel->columnChanges();
  QList<SqlColumn> keys = changes.keys();
  foreach (SqlColumn fromCol, keys) {
    SqlColumn toCol = changes[fromCol];
    if (fromCol.type() == NoType) {
      //Add column
      qDebug() << "Add col:" << toCol;
      QString sql = "alter table #caption.new# add column %1";
      QString colDef = columnDef(toCol);
      QString preparedSql = fillSqlPatternWithFields(sql).arg(colDef);
      result = execSql(preparedSql, connectionName());
    }
    else if (toCol.type() == NoType) {
      //Drop column
      qDebug() << "Drop col:" << fromCol;
      QString sql = "alter table #caption.old# drop column %1";
      QString preparedSql = fillSqlPatternWithFields(sql).arg(fromCol.name());
      result = execSql(preparedSql, connectionName());
    }
    else {
      //Change column
      qDebug() << "Col modify:" << fromCol << "to" << toCol;
      QString sql = "alter table #caption.old# change column %1 %2";
      QString preparedSql = fillSqlPatternWithFields(sql).arg(fromCol.name(), columnDef(toCol));
      result = execSql(preparedSql, connectionName());
    }
    if (!result.isSuccess())
        break;
  }
  //Rename table
  if (result.isSuccess() && isModified() && field("caption").isModified()) {
    QString sql = "alter table #caption.old# rename to #caption.new#";
    QString preparedSql = fillSqlPatternWithFields(sql);
    result = execSql(preparedSql, connectionName());
  }
  if (result.isSuccess())
    submit();

  return result;
}

void MysqlTableItem::reloadColumnsModel()
{
  //New table (not yet added)
  if (connectionName().isEmpty())
    return;
  _columnsModel->clear();
  QString sql = "SELECT table_schema, table_name, column_name, column_type, data_type, column_default, character_maximum_length, is_nullable, numeric_precision, numeric_scale, column_key, extra FROM INFORMATION_SCHEMA.COLUMNS WHERE table_schema='#databaseName#' AND table_name = '#caption#'";
  QString preparedSql = fillSqlPatternWithFields(sql);
  QSqlQuery query = SqlQueryHelper::execSql(preparedSql, connectionName());
  while (query.next()) {
    SqlColumn col(query.value("column_name").toString(), colTypeFromString(query.value("data_type").toString()));
    col.setDefaultValue(query.value("column_default"));
    col.setIsPrimary(query.value("column_key").toString() == "PRI");
    col.setLength(query.value("character_maximum_length").toInt());
    col.setPrecision(query.value("numeric_precision").toInt());
    col.setNotNull(query.value("is_nullable").toString() == "YES");
    col.setAutoIncrement(query.value("EXTRA").toString() == "auto_increment");
    _columnsModel->addSqlColumn(col, true);
  }
}

QString MysqlTableItem::createTableQuery(QString table) const
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
    colDefList.append(fillSqlPatternWithFields(pkTemplate).arg(pkColList.join(",")));
  }
  QString preparedSql = createPattern.arg(table, colDefList.join(", "));
  return preparedSql;
}

QString MysqlTableItem::columnDef(const SqlColumn &col) const
{
  QString colDef = col.name() + " " + _columnsModel->columnTypeCaption(col.type());
  if (col.length() > 0)
    colDef.append("(" + QString::number(col.length()) + ")");
  if (col.autoIncrement())
    colDef.append(" AUTO_INCREMENT");
  if (col.notNull())
    colDef = colDef.append(" NOT NULL");
  if (!col.defaultValue().isNull())
    colDef = colDef.append(" DEFAULT ").append(col.defaultValue().toString());
  return colDef;
}


