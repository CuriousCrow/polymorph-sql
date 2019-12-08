#include "sqliteplugin.h"
#include "../appconst.h"
#include "sqlitedatabase.h"
#include "sqlitetable.h"

SqlitePlugin::SqlitePlugin() : DbmsPlugin()
{
}

QString SqlitePlugin::driver()
{
  return DRIVER_SQLITE;
}

DBDatabaseItem *SqlitePlugin::newDatabaseItem(QString caption, QObject *parent)
{
  Q_UNUSED(parent)
  return new SqliteDatabase(caption);
}

DBTableItem *SqlitePlugin::newTableItem(QString caption, QObject *parent)
{
  return new SqliteTableItem(caption, parent);
}

DBViewItem *SqlitePlugin::newViewItem(QString caption, QObject *parent)
{
  Q_UNUSED(caption)
  Q_UNUSED(parent)
  return nullptr;
}

DBProcedureItem *SqlitePlugin::newProcedureItem(QString caption, QObject *parent)
{
  Q_UNUSED(caption)
  Q_UNUSED(parent)
  return nullptr;
}

DBSequenceItem *SqlitePlugin::newSequenceItem(QString caption, QObject *parent)
{
  Q_UNUSED(caption)
  Q_UNUSED(parent)
  return nullptr;
}

DBTriggerItem *SqlitePlugin::newTriggerItem(QString caption, QObject *parent)
{
  Q_UNUSED(caption)
  Q_UNUSED(parent)
  return nullptr;
}

AbstractDatabaseEditForm *SqlitePlugin::formByType(DBObjectItem::ItemType type)
{
  Q_UNUSED(type)
  return nullptr;
}
