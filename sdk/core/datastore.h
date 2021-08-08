#ifndef DATASTORE_H
#define DATASTORE_H

#include <QObject>
#include <QSqlDatabase>
#include <QTabWidget>
#include "models/lstructureitemmodel.h"
#include "models/unisqltablemodel.h"

class DataStore : public QObject
{
  Q_OBJECT
public:
  explicit DataStore(QObject *parent = nullptr);

  void setTabWidget(QTabWidget* tabWidget);
  QTabWidget* tabWidget();
  LStructureItemModel* structureModel();
  QModelIndex itemIdx(DBObjectItem* fromItem, QString folder, QString name = "");
  DBObjectItem* itemByFolderAndName(DBObjectItem* fromItem, QString folder, QString name = "");
  int databaseIdFromItem(DBObjectItem* item);
  UniSqlTableModel* historyModel(int dbId);
  QByteArray loadTableState(int dbId, QString name);
  void saveTableState(int dbId, QString name, QByteArray data);
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
