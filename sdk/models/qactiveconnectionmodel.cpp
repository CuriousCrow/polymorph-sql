#include "qactiveconnectionmodel.h"
#include <QDebug>

QActiveConnectionModel::QActiveConnectionModel(QObject *parent):
  QSortFilterProxyModel(parent)
{
}

QActiveConnectionModel::~QActiveConnectionModel()
{
}

bool QActiveConnectionModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
  //  qDebug() << "filter check:" << source_row;
  if (source_parent.isValid())
    return false;
  return sourceModel()->hasChildren(sourceModel()->index(source_row,0));
}
