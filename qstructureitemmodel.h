#ifndef QSTRUCTUREITEMMODEL_H
#define QSTRUCTUREITEMMODEL_H

#include "lstandardtreemodel.h"
#include "qdbobjectitem.h"
#include <QSqlDatabase>

class QStructureItemModel : public LStandardTreeModel
{
  Q_OBJECT
public:
  explicit QStructureItemModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());
  ~QStructureItemModel();

  void appendItem(QDBObjectItem* item, QDBObjectItem* parent = 0);
  void appendItem(QDBObjectItem* item, QModelIndex parent);

  bool deleteChildren(QModelIndex parent);

signals:
  void itemAboutToBeRemoved(QString itemUrl);

private:
  QSqlDatabase _db;
  bool loadRegisteredDatabases();
private slots:
  void onAboutToBeRemoved(const QModelIndex & parent, int first, int last);

  // QAbstractItemModel interface
public:
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // QSTRUCTUREITEMMODEL_H