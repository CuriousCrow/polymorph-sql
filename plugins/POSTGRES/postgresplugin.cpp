#include "postgresplugin.h"
#include "sdk/objects/appconst.h"
#include "postgresdatabase.h"
#include "postgrestable.h"
#include "postgressequence.h"
#include "postgrestriggeritem.h"
#include "postgresfunctionitem.h"
#include "postgresviewitem.h"
#include "postgresfolderitem.h"


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
  return new PostgresViewItem(caption, parent);
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

FolderTreeItem *PostgresPlugin::newFolderItem(QObject *parent)
{
    FolderTreeItem* folder = new PostgresFolderItem(parent);
    return folder;
}

AbstractDatabaseEditForm *PostgresPlugin::formByType(DBObjectItem::ItemType type)
{
  Q_UNUSED(type)
  return nullptr;
}

QList<DBObjectItem::ItemType> PostgresPlugin::supportedTypes()
{
  QList<DBObjectItem::ItemType> types;
  types.append(DBObjectItem::Table);
  types.append(DBObjectItem::View);
  types.append(DBObjectItem::Sequence);
  types.append(DBObjectItem::Procedure);
  types.append(DBObjectItem::Trigger);
  return types;
}

QString PostgresPlugin::folderName(DBObjectItem::ItemType type)
{
  switch (type) {
  case DBObjectItem::Table:
    return tr("Tables");
  case DBObjectItem::SystemTable:
    return tr("System tables");
  case DBObjectItem::View:
    return tr("Views");
  case DBObjectItem::Sequence:
    return tr("Sequences");
  case DBObjectItem::Procedure:
    return tr("Procedures");
  case DBObjectItem::Trigger:
    return tr("Triggers");
  default:
    return "";
  }
}
