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
  QStructureItemModel* structureModel();
signals:

public slots:

private:
  explicit DataStore(QObject *parent = nullptr);
  static DataStore* _singleton;

  QStructureItemModel* _structureModel;
  QSqlDatabase appDB;
};

#endif // DATASTORE_H
