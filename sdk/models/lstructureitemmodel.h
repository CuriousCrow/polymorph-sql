#ifndef LSTRUCTUREITEMMODEL_H
#define LSTRUCTUREITEMMODEL_H

#include "lstandardtreemodel.h"
#include "objects/dbobjectitem.h"
#include "objects/dbdatabase.h"
#include <QSqlDatabase>

class LStructureItemModel : public LStandardTreeModel
{
  Q_OBJECT
public:
  explicit LStructureItemModel(QObject *parent = nullptr);
  ~LStructureItemModel();

  void appendItem(DBObjectItem* item, DBObjectItem* parent = nullptr);
  void appendItem(DBObjectItem* item, QModelIndex parent);

  QModelIndex indexByUrl(const AppUrl &url);
  DBObjectItem* itemByUrl(const AppUrl &url);
  DBObjectItem* itemByIdx(const QModelIndex &idx);

  bool deleteChildren(QModelIndex parent);
  bool deleteChildren(DBObjectItem* parentItem);
signals:
  void itemAboutToBeRemoved(QString itemUrl);
private slots:
  void onAboutToBeRemoved(const QModelIndex & parent, int first, int last);

  // QAbstractItemModel interface
public:
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
};

#endif // LSTRUCTUREITEMMODEL_H
