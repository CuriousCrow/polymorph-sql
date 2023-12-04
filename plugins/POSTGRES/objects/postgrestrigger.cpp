#include "postgrestrigger.h"

#include "objects/appconst.h"
#include "utils/sqlqueryhelper.h"

#include <QDebug>


PostgresTriggerItem::PostgresTriggerItem()
  : DBTriggerItem()
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
  QString preparedSql = fillSqlPatternWithFields(sql);
  QSqlQuery resultSet = SqlQueryHelper::execSql(preparedSql, connectionName());
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

ActionResult PostgresTriggerItem::insertMe()
{
  qDebug() << "Create trigger" << caption();
  QString sql = toDDL();
  return execSql(sql, connectionName());
}

ActionResult PostgresTriggerItem::updateMe()
{
  ActionResult res;

  if (fieldModified(F_CAPTION)) {
    qDebug() << "Rename trigger:" << fieldOldValue(F_CAPTION) << caption();
    QString sql =
        "ALTER TRIGGER \"#caption.old#\" ON \"#table#\" "
        "RENAME TO \"#caption.new#\"";
    QString preparedSql = fillSqlPatternWithFields(sql);
    res = execSql(preparedSql, connectionName());
    if (!res.isSuccess())
      return res;
  }

  if (fieldModified(F_ENABLED)) {
    qDebug() << "Set trigger" << caption() << "enabled:" << fieldValue(F_ENABLED);
    QString sql = "ALTER TABLE \"#table#\" %1 TRIGGER \"#caption#\"";
    sql = sql.arg(fieldValue(F_ENABLED).toBool() ? "ENABLE" : "DISABLE");
    QString preparedSql = fillSqlPatternWithFields(sql);
    res = execSql(preparedSql, connectionName());
    if (!res.isSuccess())
      return res;
  }
  return ActionResult();
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

QStringList PostgresTriggerItem::events() const
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


ActionResult PostgresTriggerItem::deleteMe()
{
  refresh();
  QString sql = "drop trigger \"#caption#\" on \"#table#\"";
  QString preparedSql = fillSqlPatternWithFields(sql);
  return execSql(preparedSql, connectionName());
}

QString PostgresTriggerItem::toDDL() const
{
    QString sql =
        "CREATE TRIGGER \"#caption#\" "
        "#timing# %1 "
        "ON \"#table#\" "
        "FOR EACH ROW "
        "EXECUTE PROCEDURE #function#()";
    sql = sql.arg(events().join(" OR "));
    QString preparedSql = fillSqlPatternWithFields(sql);
    return preparedSql;
}
