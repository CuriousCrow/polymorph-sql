#include "firebirdtrigger.h"
#include "objects/appconst.h"
#include "utils/sqlqueryhelper.h"

#define TIMING_BEFORE "BEFORE"
#define TIMING_AFTER "AFTER"

FirebirdTrigger::FirebirdTrigger() : DBTriggerItem()
{
  _identifierSupport = new QuoteIdentifier();

  _mInArguments = new VariantMapTableModel();
  _mOutArguments = new VariantMapTableModel();
}

FirebirdTrigger::~FirebirdTrigger()
{
  delete _mInArguments;
  delete _mOutArguments;
}

bool FirebirdTrigger::refresh()
{
  QString sql = "select RDB$TRIGGER_NAME, RDB$RELATION_NAME \"table\", RDB$TRIGGER_TYPE event, "
                "RDB$TRIGGER_SOURCE \"function\", RDB$TRIGGER_INACTIVE \"inactive\" "
                "from RDB$TRIGGERS where RDB$SYSTEM_FLAG = 0 and RDB$TRIGGER_NAME = '#caption#'";
  QString preparedSql = fillSqlPatternWithFields(sql);
  QSqlQuery resultSet = SqlQueryHelper::execSql(preparedSql, connectionName());
  clearEventFields();
  if (resultSet.next()) {
    qDebug() << "Table:" << resultSet.value(F_TABLE);
    setFieldValue(F_TABLE, resultSet.value(F_TABLE));
    setFieldValue(F_ENABLED, resultSet.value("inactive").toInt() == 0);
    setFieldValue(F_FUNCTION, resultSet.value(F_FUNCTION));
    setEventByCode(resultSet.value("event").toInt());
    submit();
    return true;
  }
  else {
    return false;
  }
}

QString FirebirdTrigger::toDDL() const
{
  QString sql = "CREATE TRIGGER #identifier# FOR \"#table#\" #timing# %1\n"
                "AS BEGIN\n#function#\nEND";
  sql = sql.arg(events().join(" OR "));
  QString preparedSql = fillSqlPatternWithFields(sql);
  return preparedSql;
}

ActionResult FirebirdTrigger::insertMe()
{
  qDebug() << "Create trigger" << caption();
  QString sql = toDDL();
  return execSql(sql, connectionName());
}

ActionResult FirebirdTrigger::updateMe()
{
  return DBTriggerItem::updateMe();
}

ActionResult FirebirdTrigger::deleteMe()
{
  refresh();
  QString sql = "drop trigger #identifier#";
  QString preparedSql = fillSqlPatternWithFields(sql);
  return execSql(preparedSql, connectionName());
}

void FirebirdTrigger::setEventByCode(int eventType)
{
  clearEventFields();
  setFieldValue(F_TIMING, TIMING_BEFORE);

  switch (eventType) {
  case 1:
    setFieldValue(F_TIMING, TIMING_BEFORE);
    setFieldValue(F_EVENT_INSERT, true);
    break;
  case 2:
    setFieldValue(F_TIMING, TIMING_AFTER);
    setFieldValue(F_EVENT_INSERT, true);
    break;
  case 3:
    setFieldValue(F_TIMING, TIMING_BEFORE);
    setFieldValue(F_EVENT_UPDATE, true);
    break;
  case 4:
    setFieldValue(F_TIMING, TIMING_AFTER);
    setFieldValue(F_EVENT_UPDATE, true);
    break;
  case 5:
    setFieldValue(F_TIMING, TIMING_BEFORE);
    setFieldValue(F_EVENT_DELETE, true);
    break;
  case 6:
    setFieldValue(F_TIMING, TIMING_AFTER);
    setFieldValue(F_EVENT_DELETE, true);
    break;
  case 17:
    setFieldValue(F_TIMING, TIMING_BEFORE);
    setFieldValue(F_EVENT_INSERT, true);
    setFieldValue(F_EVENT_UPDATE, true);
    break;
  case 18:
    setFieldValue(F_TIMING, TIMING_AFTER);
    setFieldValue(F_EVENT_INSERT, true);
    setFieldValue(F_EVENT_UPDATE, true);
  case 25:
    setFieldValue(F_TIMING, TIMING_BEFORE);
    setFieldValue(F_EVENT_INSERT, true);
    setFieldValue(F_EVENT_DELETE, true);
    break;
  case 26:
    setFieldValue(F_TIMING, TIMING_AFTER);
    setFieldValue(F_EVENT_INSERT, true);
    setFieldValue(F_EVENT_DELETE, true);
    break;
  case 27:
    setFieldValue(F_TIMING, TIMING_BEFORE);
    setFieldValue(F_EVENT_UPDATE, true);
    setFieldValue(F_EVENT_DELETE, true);
    break;
  case 28:
    setFieldValue(F_TIMING, TIMING_AFTER);
    setFieldValue(F_EVENT_UPDATE, true);
    setFieldValue(F_EVENT_DELETE, true);
    break;
  case 113:
    setFieldValue(F_TIMING, TIMING_BEFORE);
    setFieldValue(F_EVENT_INSERT, true);
    setFieldValue(F_EVENT_UPDATE, true);
    setFieldValue(F_EVENT_DELETE, true);
    break;
  case 114:
    setFieldValue(F_TIMING, TIMING_AFTER);
    setFieldValue(F_EVENT_INSERT, true);
    setFieldValue(F_EVENT_UPDATE, true);
    setFieldValue(F_EVENT_DELETE, true);
    break;
  }

}

void FirebirdTrigger::clearEventFields()
{
  setFieldValue(F_EVENT_INSERT, false);
  setFieldValue(F_EVENT_UPDATE, false);
  setFieldValue(F_EVENT_DELETE, false);
  setFieldValue(F_EVENT_TRUNCATE, false);
}

QString FirebirdTrigger::parseActionStatement(QString statement)
{
  return statement.section(" ", -1, -1).remove("()");
}

QStringList FirebirdTrigger::events() const
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
