#include "qdbsqlitetableitem.h"
#include <QStringList>
#include "qsqlqueryhelper.h"
#include <QDebug>

QDBSqliteTableItem::QDBSqliteTableItem(QString caption, QObject *parent) : QDBTableItem(caption, parent)
{
}

bool QDBSqliteTableItem::insertMe()
{
  return !QSqlQueryHelper::execSql(createTableQuery(fieldValue("caption").toString()), connectionName()).lastError().isValid();
}

bool QDBSqliteTableItem::updateMe()
{
  qDebug() << "QDBSqliteTableItem::updateMe()";
  if (QDBTableItem::updateMe())
    return true;

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
  QSqlQueryHelper::execSql(preparedSql, connectionName());

  sql = "DROP TABLE #caption.old#";
  preparedSql = fillPatternWithFields(sql);
  QSqlQueryHelper::execSql(preparedSql, connectionName());

  //Переименовываем новую таблицу обратно
  sql = "ALTER TABLE tempTable RENAME TO #caption.new#";
  preparedSql = fillPatternWithFields(sql);
  QSqlQueryHelper::execSql(preparedSql, connectionName());

  submit();

  return true;
}

QString QDBSqliteTableItem::createTableQuery(QString table)
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
