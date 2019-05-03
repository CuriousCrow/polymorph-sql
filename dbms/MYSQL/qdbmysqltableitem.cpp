#include "qdbmysqltableitem.h"
#include "qsqlqueryhelper.h"
#include <QDebug>
#include <QUrl>

QDBMysqlTableItem::QDBMysqlTableItem(QString caption, QObject *parent) : QDBTableItem(caption, parent)
{
  _columnsModel = new MysqlTableColumnModel();
}

QDBMysqlTableItem::~QDBMysqlTableItem()
{
  delete _columnsModel;
}

bool QDBMysqlTableItem::insertMe()
{
  QSqlQueryHelper::execSql(createTableQuery(fieldValue("caption").toString()), connectionName());
  return submit();
}

bool QDBMysqlTableItem::updateMe()
{
  qDebug() << "QDBMysqlTableItem::updateMe()";
  if (QDBTableItem::updateMe())
    return true;

  QHash<SqlColumn, SqlColumn> changes = _columnsModel->columnChanges();
  foreach (SqlColumn fromCol, changes.keys()) {
    SqlColumn toCol = changes[fromCol];
    if (fromCol.type() == ColumnType::NoType) {
      //Добавление колонки
      qDebug() << "Add col:" << toCol;
      QString sql = "alter table #caption.new# add column %1";
      QString colDef = columnDef(toCol);
      QString preparedSql = fillPatternWithFields(sql).arg(colDef);
      QSqlQueryHelper::execSql(preparedSql, connectionName());
    }
    else if (toCol.type() == ColumnType::NoType) {
      //Удаление колонки
      qDebug() << "Drop col:" << fromCol;
      QString sql = "alter table #caption.old# drop column %1";
      QString preparedSql = fillPatternWithFields(sql).arg(fromCol.name());
      QSqlQueryHelper::execSql(preparedSql, connectionName());
    }
    else {
      //Изменения колонки
      qDebug() << "Col modify:" << fromCol << "to" << toCol;
      QString sql = "alter table #caption.old# change column %1 %2";
      QString preparedSql = fillPatternWithFields(sql).arg(fromCol.name()).arg(columnDef(toCol));
      QSqlQueryHelper::execSql(preparedSql, connectionName());
    }
  }
  //Переименование таблицы
  if (isModified() && field("caption").isModified()) {
    QString sql = "alter table #caption.old# rename to #caption.new#";
    QString preparedSql = fillPatternWithFields(sql);
    QSqlQueryHelper::execSql(preparedSql, connectionName());
  }
  submit();

  return true;
}

void QDBMysqlTableItem::reloadColumnsModel()
{
  //Новая, еще не вставленная таблица
  if (connectionName().isEmpty())
    return;
  _columnsModel->clear();
  QString sql = "SELECT table_schema, table_name, column_name, column_type, data_type, column_default, character_maximum_length, is_nullable, numeric_precision, numeric_scale, column_key, extra FROM INFORMATION_SCHEMA.COLUMNS WHERE table_schema='#databaseName#' AND table_name = '#caption#'";
  QString preparedSql = fillPatternWithFields(sql);
  QSqlQuery query = QSqlQueryHelper::execSql(preparedSql, connectionName());
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

QString QDBMysqlTableItem::createTableQuery(QString table)
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

ColumnType QDBMysqlTableItem::colTypeFromString(QString strType)
{
  qDebug() << "Field type:" << strType;
  if (strType.compare("varchar", Qt::CaseInsensitive) == 0) {
    return ColumnType::Varchar;
  }
  else if (strType.compare("bigint", Qt::CaseInsensitive) == 0) {
    return ColumnType::BigInt;
  }
  else if (strType.compare("int", Qt::CaseInsensitive) == 0) {
    return ColumnType::Integer;
  }
  else if (strType.compare("smallint", Qt::CaseInsensitive) == 0) {
    return ColumnType::SmallInt;
  }
  else if (strType.compare("numeric", Qt::CaseInsensitive) == 0
           || strType.compare("decimal", Qt::CaseInsensitive) == 0) {
    return ColumnType::Numeric;
  }
  else if (strType.compare("char", Qt::CaseInsensitive) == 0) {
    return ColumnType::Char;
  }
  else if (strType.compare("date", Qt::CaseInsensitive) == 0) {
    return ColumnType::Date;
  }
  else if (strType.compare("time", Qt::CaseInsensitive) == 0) {
    return ColumnType::Time;
  }
  else if (strType.compare("timestamp", Qt::CaseInsensitive) == 0) {
    return ColumnType::Timestamp;
  }
  else if (strType.compare("blob", Qt::CaseInsensitive) == 0) {
    return ColumnType::Blob;
  }
  Q_ASSERT_X(false, "colTypeFromString", "Unsupported field type");
  return ColumnType::NoType;
}

QString QDBMysqlTableItem::columnDef(const SqlColumn &col)
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


