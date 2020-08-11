#ifndef SQLITEPLUGIN_H
#define SQLITEPLUGIN_H

#include <QObject>
#include "../dbmsplugin.h"

class SqlitePlugin : public DbmsPlugin
{
public:
  SqlitePlugin();

  // DbmsPlugin interface
public:
  virtual QString driver() override;
  virtual DBDatabaseItem *newDatabaseItem(QString caption, QObject *parent) override;
  virtual DBTableItem *newTableItem(QString caption, QObject *parent) override;
  virtual DBViewItem *newViewItem(QString caption, QObject *parent) override;
  virtual DBProcedureItem *newProcedureItem(QString caption, QObject *parent) override;
  virtual DBSequenceItem *newSequenceItem(QString caption, QObject *parent) override;
  virtual DBTriggerItem *newTriggerItem(QString caption, QObject *parent) override;
  virtual AbstractDatabaseEditForm *formByType(DBObjectItem::ItemType type) override;
  virtual FolderTreeItem *loadFolder(FolderTreeItem *folderItem, DBObjectItem::ItemType childrenType) override;

  void loadSequences(FolderTreeItem* folderItem);
  void loadTables(FolderTreeItem* folderItem);
  void loadSysTables(FolderTreeItem* folderItem);
  void loadViews(FolderTreeItem* folderItem);
  void loadTriggers(FolderTreeItem* folderItem);
  void loadProcedures(FolderTreeItem* folderItem);

  virtual QList<DBObjectItem::ItemType> supportedTypes() override;
  virtual QString folderName(DBObjectItem::ItemType type) override;
};

#endif // SQLITEPLUGIN_H
