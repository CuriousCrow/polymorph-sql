#ifndef DBMSSUPPORT_H
#define DBMSSUPPORT_H

#include <QObject>
#include "dbsequence.h"
#include "dbprocedure.h"
#include "dbtableitem.h"
#include "dbtrigger.h"
#include "dbview.h"
#include "dbdatabase.h"
#include "foldertreeitem.h"
#include "forms/abstractdatabaseitemform.h"

class DbmsPlugin : public QObject
{
  Q_OBJECT
public:
  virtual QString driver() = 0;
  virtual DBDatabaseItem* newDatabaseItem(QString caption, QObject* parent = nullptr) = 0;
  virtual DBTableItem* newTableItem(QString caption, QObject* parent = nullptr) = 0;
  virtual DBViewItem* newViewItem(QString caption, QObject* parent = nullptr) = 0;
  virtual DBProcedureItem* newProcedureItem(QString caption, QObject* parent = nullptr) = 0;
  virtual DBSequenceItem* newSequenceItem(QString caption, QObject* parent = nullptr) = 0;
  virtual DBTriggerItem* newTriggerItem(QString caption, QObject* parent = nullptr) = 0;
  virtual FolderTreeItem* newFolderItem(QObject* parent = nullptr) = 0;

  virtual QList<DBObjectItem::ItemType> supportedTypes() = 0;

  virtual AbstractDatabaseEditForm *formByType(DBObjectItem::ItemType type) = 0;

  virtual QString folderName(DBObjectItem::ItemType type) = 0;
};

//Объявление идентификатора интерфейса
#define DbmsPlugin_iid "ru.levolex.dbmsplugin"
//Макрос объявляющий интерфейс
Q_DECLARE_INTERFACE(DbmsPlugin, DbmsPlugin_iid)


#endif // DBMSSUPPORT_H
