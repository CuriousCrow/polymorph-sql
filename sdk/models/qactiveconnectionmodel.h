#ifndef QACTIVECONNECTIONMODEL_H
#define QACTIVECONNECTIONMODEL_H

#include <QSortFilterProxyModel>

class QActiveConnectionModel : public QSortFilterProxyModel
{
public:
  QActiveConnectionModel(QObject *parent = nullptr);
  ~QActiveConnectionModel();
protected:
  virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
};

#endif // QACTIVECONNECTIONMODEL_H
