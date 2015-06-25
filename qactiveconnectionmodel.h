#ifndef QACTIVECONNECTIONMODEL_H
#define QACTIVECONNECTIONMODEL_H

#include <QSortFilterProxyModel>

class QActiveConnectionModel : public QSortFilterProxyModel
{
public:
  QActiveConnectionModel(QObject *parent = 0);
  ~QActiveConnectionModel();
protected:
  virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
};

#endif // QACTIVECONNECTIONMODEL_H
