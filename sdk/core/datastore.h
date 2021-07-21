#ifndef DATASTORE_H
#define DATASTORE_H

#include <QObject>
#include <QSqlDatabase>
#include "../models/qstructureitemmodel.h"
#include "../models/unisqltablemodel.h"

class DataStore : public QObject
{
  Q_OBJECT
public:
  explicit DataStore(QObject *parent = nullptr);

  QStructureItemModel* structureModel();
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
  QStructureItemModel* _structureModel;
  QSqlDatabase appDB;
  UniSqlTableModel* _queryHistoryModel;
};

#endif // DATASTORE_H
