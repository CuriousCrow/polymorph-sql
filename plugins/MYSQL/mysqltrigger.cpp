#include "mysqltrigger.h"
#include "objects/appconst.h"
#include "utils/sqlqueryhelper.h"
#include <QDebug>

MysqlTrigger::MysqlTrigger() : DBTriggerItem()
{
  _identifierSupport = new BacktickIdentifier();
}


bool MysqlTrigger::refresh()
{
  QString sql = "select trigger_name name, action_timing timing, event_manipulation event, event_object_table \"table\", action_statement \"function\" "
      "from INFORMATION_SCHEMA.TRIGGERS "
      "where trigger_schema='#databaseName#' and trigger_name='#caption#'";
  QString preparedSql = fillSqlPatternWithFields(sql);
  QSqlQuery resultSet = SqlQueryHelper::execSql(preparedSql, connectionName());
  clearEventFields();
  if (resultSet.next()) {
    qDebug() << "Table:" << resultSet.value(F_TABLE);
    setFieldValue(F_TABLE, resultSet.value(F_TABLE));
    setFieldValue(F_TIMING, resultSet.value(F_TIMING));
    setFieldValue(F_FUNCTION, resultSet.value(F_FUNCTION));
    setFieldValue(F_ENABLED, true);
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

QString MysqlTrigger::toDDL() const
{
  QString sql =
      "CREATE TRIGGER #identifier# "
      "#timing# %1 "
      "ON `#table#` "
      "FOR EACH ROW "
      "#function#";
  sql = sql.arg(events().join(" OR "));
  QString preparedSql = fillSqlPatternWithFields(sql);
  return preparedSql;
}

ActionResult MysqlTrigger::insertMe()
{
  qDebug() << "Create trigger" << caption();
  QString sql = toDDL();
  return execSql(sql, connectionName());
}

ActionResult MysqlTrigger::updateMe()
{
  return DBTriggerItem::updateMe();
}

ActionResult MysqlTrigger::deleteMe()
{
  refresh();
  QString sql = "drop trigger if exists #identifier#";
  QString preparedSql = fillSqlPatternWithFields(sql);
  return execSql(preparedSql, connectionName());
}

void MysqlTrigger::setEventByName(QString event)
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

void MysqlTrigger::clearEventFields()
{
  setFieldValue(F_EVENT_INSERT, false);
  setFieldValue(F_EVENT_UPDATE, false);
  setFieldValue(F_EVENT_DELETE, false);
  setFieldValue(F_EVENT_TRUNCATE, false);
}

QString MysqlTrigger::parseActionStatement(QString statement)
{
  return statement.section(" ", -1, -1).remove("()");
}

QStringList MysqlTrigger::events() const
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
