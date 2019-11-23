#include "postgrestriggeritem.h"
#include "../../qsqlqueryhelper.h"
#include "../appconst.h"
#include <QDebug>


PostgresTriggerItem::PostgresTriggerItem(QString caption, QObject *parent)
  : QDBTriggerItem(caption, parent)
{
}

bool PostgresTriggerItem::refresh()
{
  QString sql =
      "SELECT event_manipulation \"event\", event_object_table \"table\", "
      "action_timing \"timing\", action_statement \"function\", "
      "(select tgenabled from pg_trigger where tgname='#caption#') enabled "
      "FROM information_schema.triggers "
      "where trigger_name='#caption#'";
  QString preparedSql = fillSqlPattern(sql);
  QSqlQuery resultSet = QSqlQueryHelper::execSql(preparedSql, connectionName());
  clearEventFields();
  if (resultSet.next()) {
    qDebug() << "Table:" << resultSet.value(F_TABLE);
    setFieldValue(F_TABLE, resultSet.value(F_TABLE));
    setFieldValue(F_TIMING, resultSet.value(F_TIMING));
    setFieldValue(F_FUNCTION, parseActionStatement(resultSet.value(F_FUNCTION).toString()));
    setFieldValue(F_ENABLED, resultSet.value(F_ENABLED).toString() == "O"); //"0" - Enabled, "D" - Disabled
    setEventByName(resultSet.value("event").toString());
    while (resultSet.next()) {
      setEventByName(resultSet.value("event").toString());
    }
    submit();
    return true;
  }
  else {
    return false;
  }
}

bool PostgresTriggerItem::insertMe()
{
  qDebug() << "Create trigger" << fieldValue(F_CAPTION);
  QString sql =
      "CREATE TRIGGER \"#caption#\" "
      "#timing# %1 "
      "ON \"#table#\" "
      "FOR EACH ROW "
      "EXECUTE PROCEDURE #function#";
  sql = sql.arg(events().join(" OR "));
  QString preparedSql = fillPatternWithFields(sql);
  return !QSqlQueryHelper::execSql(preparedSql, connectionName()).lastError().isValid();
}

bool PostgresTriggerItem::updateMe()
{
  if (fieldModified(F_CAPTION)) {
    qDebug() << "Rename trigger:" << fieldOldValue(F_CAPTION) << fieldValue(F_CAPTION);
    QString sql =
        "ALTER TRIGGER \"#caption.old#\" ON \"#table#\" "
        "RENAME TO \"#caption.new#\"";
    QString preparedSql = fillPatternWithFields(sql);
    QSqlQueryHelper::execSql(preparedSql, connectionName());
  }

  if (fieldModified(F_ENABLED)) {
    qDebug() << "Set trigger" << fieldValue(F_CAPTION) << "enabled:" << fieldValue(F_ENABLED);
    QString sql = "ALTER TABLE \"#table#\" %1 TRIGGER \"#caption#\"";
    sql = sql.arg(fieldValue(F_ENABLED).toBool() ? "ENABLE" : "DISABLE");
    QString preparedSql = fillPatternWithFields(sql);
    QSqlQueryHelper::execSql(preparedSql, connectionName());
  }
  return true;
}

void PostgresTriggerItem::setEventByName(QString event)
{
  if (event == "INSERT")
    setFieldValue(F_EVENT_INSERT, true);
  else if (event == "UPDATE")
    setFieldValue(F_EVENT_UPDATE, true);
  else if (event == "DELETE")
    setFieldValue(F_EVENT_DELETE, true);
  else if (event == "TRUNCATE")
    setFieldValue(F_EVENT_TRUNCATE, true);
  else {
    qWarning() << "Unknown trigger event";
  }
}

void PostgresTriggerItem::clearEventFields()
{
  setFieldValue(F_EVENT_INSERT, false);
  setFieldValue(F_EVENT_UPDATE, false);
  setFieldValue(F_EVENT_DELETE, false);
  setFieldValue(F_EVENT_TRUNCATE, false);
}

QString PostgresTriggerItem::parseActionStatement(QString statement)
{
  return statement.section(" ", -1, -1).remove("()");
}

QStringList PostgresTriggerItem::events()
{
  QStringList list;
  if (fieldValue(F_EVENT_INSERT).toBool())
    list.append("INSERT");
  if (fieldValue(F_EVENT_UPDATE).toBool())
    list.append("UPDATE");
  if (fieldValue(F_EVENT_DELETE).toBool())
    list.append("DELETE");
  if (fieldValue(F_EVENT_TRUNCATE).toBool())
    list.append("TRUNCATE");
  return list;
}


bool PostgresTriggerItem::deleteMe()
{
  refresh();
  QString sql = "drop trigger \"#caption#\" on \"#table#\"";
  QString preparedSql = fillSqlPattern(sql);
  return !QSqlQueryHelper::execSql(preparedSql, connectionName()).lastError().isValid();
}
