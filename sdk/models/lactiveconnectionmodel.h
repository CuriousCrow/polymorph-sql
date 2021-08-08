#ifndef LACTIVECONNECTIONMODEL_H
#define LACTIVECONNECTIONMODEL_H

#include <QSortFilterProxyModel>

class LActiveConnectionModel : public QSortFilterProxyModel
{
public:
  LActiveConnectionModel(QObject *parent = nullptr);
  ~LActiveConnectionModel();
protected:
  virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
};

#endif // LACTIVECONNECTIONMODEL_H
