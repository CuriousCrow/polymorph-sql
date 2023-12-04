#ifndef DATASTORE_H
#define DATASTORE_H

#include <QObject>
#include <QSqlDatabase>
#include <QTabWidget>
#include "models/lstructureitemmodel.h"
#include "models/unisqltablemodel.h"
#include "objects/dbdatabase.h"

class DataStore : public QObject
{
  Q_OBJECT
public:
  explicit DataStore(QObject *parent = nullptr);

  void setTabWidget(QTabWidget* tabWidget);
  //Access to main window tab widget
  QTabWidget* tabWidget();
  LStructureItemModel* structureModel();
  QModelIndex itemIdx(DBObjectItem* fromItem, QString folder, QString name = "");
  DBObjectItem* itemByFolderAndName(DBObjectItem* fromItem, QString folder, QString name = "");
  DBDatabaseItem* databaseItem(DBObjectItem* item);
  int databaseIdFromItem(DBObjectItem* item);
  UniSqlTableModel* historyModel(int dbId);
  //Table state
  QByteArray loadTableState(int dbId, QString name);
  void saveTableState(int dbId, QString name, QByteArray data);
  void resetTableState(int dbId, QString name);

  bool addQueryHistoryItem(int dbId, QString query);
  bool clearQueryHistory(int dbId);

  void initRegisteredDatabases();
signals:

public slots:

private:
  LStructureItemModel* _structureModel;
  QTabWidget* _tabWidget;
  QSqlDatabase appDB;
  UniSqlTableModel* _queryHistoryModel;
};

#endif // DATASTORE_H
