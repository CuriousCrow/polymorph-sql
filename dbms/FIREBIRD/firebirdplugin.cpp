#include "firebirdplugin.h"
#include "../appconst.h"
#include "firebirddatabase.h"
#include "firebirdtable.h"


FirebirdPlugin::FirebirdPlugin()
{

}


QString FirebirdPlugin::driver()
{
  return DRIVER_FIREBIRD;
}

DBDatabaseItem *FirebirdPlugin::newDatabaseItem(QString caption, QObject *parent)
{
  Q_UNUSED(parent)
  return new FirebirdDatabase(caption);
}

DBTableItem *FirebirdPlugin::newTableItem(QString caption, QObject *parent)
{
  return new FirebirdTable(caption, parent);
}

DBViewItem *FirebirdPlugin::newViewItem(QString caption, QObject *parent)
{
  Q_UNUSED(caption)
  Q_UNUSED(parent)
  return nullptr;
}

DBProcedureItem *FirebirdPlugin::newProcedureItem(QString caption, QObject *parent)
{
  Q_UNUSED(caption)
  Q_UNUSED(parent)
  return nullptr;
}

DBSequenceItem *FirebirdPlugin::newSequenceItem(QString caption, QObject *parent)
{
  Q_UNUSED(caption)
  Q_UNUSED(parent)
  return nullptr;
}

DBTriggerItem *FirebirdPlugin::newTriggerItem(QString caption, QObject *parent)
{
  Q_UNUSED(caption)
  Q_UNUSED(parent)
  return nullptr;
}

AbstractDatabaseEditForm *FirebirdPlugin::formByType(DBObjectItem::ItemType type)
{
  Q_UNUSED(type)
  return nullptr;
}
