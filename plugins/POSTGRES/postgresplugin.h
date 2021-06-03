#ifndef POSTGRESPLUGIN_H
#define POSTGRESPLUGIN_H

#include <QObject>
#include "sdk/objects/dbmsplugin.h"

class PostgresPlugin : public DbmsPlugin
{
  Q_OBJECT
public:
  // DbmsPlugin interface
public:
  virtual QString driver() override;
  virtual DBDatabaseItem *newDatabaseItem(QString caption, QObject *parent) override;
  virtual DBTableItem *newTableItem(QString caption, QObject *parent) override;
  virtual DBViewItem *newViewItem(QString caption, QObject *parent) override;
  virtual DBProcedureItem *newProcedureItem(QString caption, QObject *parent) override;
  virtual DBSequenceItem *newSequenceItem(QString caption, QObject *parent) override;
  virtual DBTriggerItem *newTriggerItem(QString caption, QObject *parent) override;
  virtual FolderTreeItem *newFolderItem(DBObjectItem::ItemType type, QObject *parent) override;
  virtual AbstractDatabaseEditForm *formByType(DBObjectItem::ItemType type) override;
  virtual FolderTreeItem *loadFolder(FolderTreeItem *folderItem, DBObjectItem::ItemType childrenType) override;

  void loadSequences(FolderTreeItem* folderItem);
  void loadTables(FolderTreeItem* folderItem);
  void loadViews(FolderTreeItem* folderItem);
  void loadTriggers(FolderTreeItem* folderItem);
  void loadProcedures(FolderTreeItem* folderItem);

  virtual QList<DBObjectItem::ItemType> supportedTypes() override;
  virtual QString folderName(DBObjectItem::ItemType type) override;
};

#endif // POSTGRESPLUGIN_H
