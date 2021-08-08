#include "lactiveconnectionmodel.h"
#include <QDebug>

LActiveConnectionModel::LActiveConnectionModel(QObject *parent):
  QSortFilterProxyModel(parent)
{
}

LActiveConnectionModel::~LActiveConnectionModel()
{
}

bool LActiveConnectionModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
  //  qDebug() << "filter check:" << source_row;
  if (source_parent.isValid())
    return false;
  return sourceModel()->hasChildren(sourceModel()->index(source_row,0));
}
