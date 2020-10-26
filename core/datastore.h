#ifndef DATASTORE_H
#define DATASTORE_H

#include <QObject>
#include <QSqlDatabase>
#include "../qstructureitemmodel.h"
#include "../models/unisqltablemodel.h"

class DataStore : public QObject
{
  Q_OBJECT
public:
  static DataStore* instance(QObject* parent = nullptr);
  static QStructureItemModel* structureModel();
  static QModelIndex itemIdx(DBObjectItem* fromItem, QString folder, QString name = "");
  static DBObjectItem* itemByFolderAndName(DBObjectItem* fromItem, QString folder, QString name = "");
  static UniSqlTableModel* historyModel(int dbId);
  static bool addQueryHistoryItem(int dbId, QString query);
signals:

public slots:

private:
  explicit DataStore(QObject *parent = nullptr);
  static DataStore* _singleton;

  void initRegisteredDatabases();

  QStructureItemModel* _structureModel;
  QSqlDatabase appDB;
  UniSqlTableModel* _queryHistoryModel;
};

#endif // DATASTORE_H
