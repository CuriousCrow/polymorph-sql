#include "qdbpostgrestableitem.h"
#include <QSqlQuery>
#include <QDebug>
#include "qsqlqueryhelper.h"

QDBPostgresTableItem::QDBPostgresTableItem(QString caption, QObject *parent) : QDBTableItem(caption, parent)
{
  _columnsModel = new PostgresTableColumnModel();
}

QDBPostgresTableItem::~QDBPostgresTableItem()
{
  delete _columnsModel;
}

bool QDBPostgresTableItem::insertMe()
{
  QSqlQueryHelper::execSql(createTableQuery(caption()), connectionName());
  return submit();
}

bool QDBPostgresTableItem::updateMe()
{
  return false;
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
    col.setNotNull(query.value("is_nullable").toString() == "YES");
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

ColumnType QDBPostgresTableItem::colTypeFromString(QString strType)
{
  qDebug() << "String coltype:" << strType;
  if (strType.compare("bigint", Qt::CaseInsensitive) == 0) {
    return ColumnType::BigInt;
  }
  else if (strType.compare("integer", Qt::CaseInsensitive) == 0) {
    return ColumnType::Integer;
  }
  else if (strType.compare("smallint", Qt::CaseInsensitive) == 0) {
    return ColumnType::SmallInt;
  }
  else if (strType.compare("character varying", Qt::CaseInsensitive) == 0) {
    return ColumnType::Varchar;
  }
  else if (strType.compare("boolean", Qt::CaseInsensitive) == 0) {
    return ColumnType::Boolean;
  }
  else if (strType.startsWith("timestamp", Qt::CaseInsensitive)) {
    return ColumnType::Timestamp;
  }
  else if (strType.startsWith("time", Qt::CaseInsensitive)) {
    return ColumnType::Time;
  }
  else if (strType.startsWith("date", Qt::CaseInsensitive)) {
    return ColumnType::Date;
  }
  else if (strType.compare("\"char\"", Qt::CaseInsensitive) == 0) {
    return ColumnType::Char;
  }
  else if (strType.compare("blob", Qt::CaseInsensitive) == 0) {
    return ColumnType::Blob;
  }
  else if (strType.compare("numeric", Qt::CaseInsensitive) == 0) {
    return ColumnType::Numeric;
  }
  else {
    Q_ASSERT_X(false, "colTypeFromString", "Unknown data type");
  }
  return ColumnType::NoType;
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
