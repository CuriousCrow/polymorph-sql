#include "postgresplugin.h"
#include "../appconst.h"
#include "postgresdatabase.h"
#include "postgrestable.h"
#include "postgressequence.h"
#include "postgrestriggeritem.h"
#include "postgresfunctionitem.h"


QString PostgresPlugin::driver()
{
  return DRIVER_PSQL;
}

DBDatabaseItem *PostgresPlugin::newDatabaseItem(QString caption, QObject *parent)
{
  Q_UNUSED(parent)
  return new PostgresDatabase(caption);
}

DBTableItem *PostgresPlugin::newTableItem(QString caption, QObject *parent)
{
  return new PostgresTable(caption, parent);
}

DBViewItem *PostgresPlugin::newViewItem(QString caption, QObject *parent)
{
  Q_UNUSED(caption)
  Q_UNUSED(parent)
  return nullptr;
}

DBProcedureItem *PostgresPlugin::newProcedureItem(QString caption, QObject *parent)
{
  return new PostgresFunctionItem(caption, parent);
}

DBSequenceItem *PostgresPlugin::newSequenceItem(QString caption, QObject *parent)
{
  return new PostgresSequence(caption, parent);
}

DBTriggerItem *PostgresPlugin::newTriggerItem(QString caption, QObject *parent)
{
  return new PostgresTriggerItem(caption, parent);
}

AbstractDatabaseEditForm *PostgresPlugin::formByType(DBObjectItem::ItemType type)
{
  Q_UNUSED(type)
  return nullptr;
}
