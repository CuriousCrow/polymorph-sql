#ifndef DATASTORE_H
#define DATASTORE_H

#include <QObject>
#include <QSqlDatabase>
#include "../qstructureitemmodel.h"

class DataStore : public QObject
{
  Q_OBJECT
public:
  static DataStore* instance(QObject* parent = nullptr);
  static QStructureItemModel* structureModel();
  static QModelIndex itemIdx(DBObjectItem* fromItem, QString folder, QString name = "");
  static DBObjectItem* itemByFolderAndName(DBObjectItem* fromItem, QString folder, QString name = "");
signals:

public slots:

private:
  explicit DataStore(QObject *parent = nullptr);
  static DataStore* _singleton;

  QStructureItemModel* _structureModel;
  QSqlDatabase appDB;
};

#endif // DATASTORE_H
