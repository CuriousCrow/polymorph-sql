#ifndef QSTRUCTUREITEMMODEL_H
#define QSTRUCTUREITEMMODEL_H

#include "lstandardtreemodel.h"
#include "dbms/qdbobjectitem.h"
#include "dbms/qdbdatabaseitem.h"
#include <QSqlDatabase>

class QStructureItemModel : public LStandardTreeModel
{
  Q_OBJECT
public:
  explicit QStructureItemModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
  ~QStructureItemModel();

  void appendItem(QDBObjectItem* item, QDBObjectItem* parent = nullptr);
  void appendItem(QDBObjectItem* item, QModelIndex parent);

  bool deleteChildren(QModelIndex parent);
signals:
  void itemAboutToBeRemoved(QString itemUrl);
private:
  QSqlDatabase _db;
  bool loadRegisteredDatabases();
  //Fabric method
  QDBDatabaseItem* dbItemByDriver(QString caption, QString driverName);
private slots:
  void onAboutToBeRemoved(const QModelIndex & parent, int first, int last);

  // QAbstractItemModel interface
public:
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // QSTRUCTUREITEMMODEL_H
