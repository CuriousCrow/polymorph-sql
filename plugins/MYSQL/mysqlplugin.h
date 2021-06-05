#ifndef MYSQLPLUGIN_H
#define MYSQLPLUGIN_H

#include <QObject>
#include "sdk/objects/dbmsplugin.h"

class MysqlPlugin : public DbmsPlugin
{
  Q_OBJECT
  // DbmsPlugin interface
public:
  virtual QString driver() override;
  virtual DBDatabaseItem *newDatabaseItem(QString caption, QObject *parent) override;
  virtual DBTableItem *newTableItem(QString caption, QObject *parent) override;
  virtual DBViewItem *newViewItem(QString caption, QObject *parent) override;
  virtual DBProcedureItem *newProcedureItem(QString caption, QObject *parent) override;
  virtual DBSequenceItem *newSequenceItem(QString caption, QObject *parent) override;
  virtual DBTriggerItem *newTriggerItem(QString caption, QObject *parent) override;
  virtual FolderTreeItem *newFolderItem(QObject *parent) override;
  virtual AbstractDatabaseEditForm *formByType(DBObjectItem::ItemType type) override;

  // DbmsPlugin interface
public:
  virtual FolderTreeItem *loadFolder(FolderTreeItem *folderItem, DBObjectItem::ItemType childrenType) override;
  virtual QList<DBObjectItem::ItemType> supportedTypes() override;
  virtual QString folderName(DBObjectItem::ItemType type) override;
};

#endif // MYSQLPLUGIN_H
