#include "sqlitetable.h"
#include <QStringList>
#include "qsqlqueryhelper.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlField>
#include "sdk/objects/appconst.h"

SqliteTableItem::SqliteTableItem()
  : DBTableItem()
{
  _columnsModel = new SqlColumnModel();

  _constraintsModel = new VariantMapTableModel();
  _constraintsModel->registerColumn(F_TYPE, tr("Type"));
  _constraintsModel->registerColumn(F_NAME, tr("Name"));
}

SqliteTableItem::~SqliteTableItem()
{
  delete _columnsModel;
  delete _constraintsModel;
}

void SqliteTableItem::reloadColumnsModel()
{
  _columnsModel->clear();
  QSqlRecord sqlColumns = QSqlQueryHelper::tableRowInfo(
        this->caption(),
        connectionName());
  for (int i=0; i<sqlColumns.count(); i++) {
    QSqlField field = sqlColumns.field(i);
    int colType = NoType;
    switch (field.type()) {
    case QVariant::String:
      colType = colTypeFromString("TEXT");
      break;
    case QVariant::Int:
      colType = colTypeFromString("INTEGER");
      break;
    case QVariant::Double:
      colType = colTypeFromString("REAL");
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

ActionResult SqliteTableItem::insertMe()
{
  return execSql(createTableQuery(caption()), connectionName());
}

ActionResult SqliteTableItem::updateMe()
{
  qDebug() << "QDBSqliteTableItem::updateMe()";
  ActionResult res = DBTableItem::updateMe();
  if (res.isSuccess())
    return res;

  //Создание новой таблицы
  QString sql = createTableQuery("tempTable");
  QSqlQueryHelper::execSql(sql, connectionName());

  //Перенос данных сохранившихся колонок в новую таблицу
  QHash<QString, QString> colNames = _columnsModel->permanentColNames();
  QStringList oldNames;
  QStringList newNames;
  foreach (QString oldName, colNames.keys()) {
    oldNames.append(oldName);
    newNames.append(colNames.value(oldName));
  }
  sql = "INSERT INTO tempTable (%1) SELECT %2 FROM #caption.old#";
  QString preparedSql = fillPatternWithFields(sql).arg(newNames.join(", "), oldNames.join(", "));
  res = execSql(preparedSql, connectionName());
  if (!res.isSuccess())
    return res;

  sql = "DROP TABLE #caption.old#";
  preparedSql = fillPatternWithFields(sql);
  res = execSql(preparedSql, connectionName());
  if (!res.isSuccess())
    return res;

  //Переименовываем новую таблицу обратно
  sql = "ALTER TABLE tempTable RENAME TO #caption.new#";
  preparedSql = fillPatternWithFields(sql);
  res = execSql(preparedSql, connectionName());
  if (!res.isSuccess())
    return res;

  return ActionResult();
}

QString SqliteTableItem::createTableQuery(QString table) const
{
  QString createPattern = "CREATE TABLE %1 (%2);";
  QStringList pkColList;
  QStringList colDefList;
  bool rowIdPk = _columnsModel->hasOnlyIntegerPK();
  for(int i=0; i<_columnsModel->rowCount(); i++) {
    SqlColumn col = _columnsModel->columnByIndex(i);
    if (!rowIdPk && col.isPrimary())
      pkColList.append(col.name());
    QString colDef = col.name() + " " + _columnsModel->columnTypeCaption(col.type());
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
    colDefList.append(fillPatternWithFields(pkTemplate).arg(pkColList.join(",")));
  }
  QString preparedSql = createPattern.arg(table).arg(colDefList.join(", "));
  return preparedSql;
}
