#include "qstructureitemmodel.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "../objects/appconst.h"
#include <QDebug>
#include "../objects/appurl.h"
#include "../utils/qsqlqueryhelper.h"

#define TREEMODEL_DEBUG

QStructureItemModel::QStructureItemModel(QObject *parent):
  LStandardTreeModel(parent)
{
  connect(this, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
          SLOT(onAboutToBeRemoved(QModelIndex,int,int)));
}

QStructureItemModel::~QStructureItemModel()
{
}

void QStructureItemModel::appendItem(DBObjectItem *item, DBObjectItem *parent)
{
  addItem(item, parent);
  if (parent)
    item->setParentUrl(parent->objectUrl());
  else
    item->setParentUrl(AppUrl());
}

void QStructureItemModel::appendItem(DBObjectItem *item, QModelIndex parent)
{
  addItem(item, parent);
  if (parent.isValid()) {
    DBObjectItem* parentItem = itemByIdx(parent);
    Q_ASSERT(parentItem);
    item->setParentUrl(parentItem->objectUrl());
  }
}

QModelIndex QStructureItemModel::indexByUrl(const AppUrl &url)
{
  return indexByName(url.toString());
}

DBObjectItem *QStructureItemModel::itemByUrl(const AppUrl &url)
{
    return static_cast<DBObjectItem*>(itemByName(url.toString()));
}

DBObjectItem *QStructureItemModel::itemByIdx(const QModelIndex &idx)
{
    return static_cast<DBObjectItem*>(itemByIndex(idx));
}

bool QStructureItemModel::deleteChildren(QModelIndex parent)
{
    return removeRows(0, rowCount(parent), parent);
}

bool QStructureItemModel::deleteChildren(DBObjectItem *parentItem)
{
    return deleteChildren(indexByItem(parentItem));
}

void QStructureItemModel::onAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
  for (int row=first; row<last; row++){
    DBObjectItem* item = static_cast<DBObjectItem*>(itemByIndex(index(row, 0, parent)));
    emit itemAboutToBeRemoved(item->objectUrl().toString());
  }
}


Qt::ItemFlags QStructureItemModel::flags(const QModelIndex &index) const
{
  DBObjectItem* item = static_cast<DBObjectItem*>(itemByIndex(index));
  if ((item->type() == DBObjectItem::Database)
      && item->children().count() > 0){
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QVariant QStructureItemModel::data(const QModelIndex &index, int role) const
{
#ifdef TREEMODEL_DEBUG
    if (!index.isValid())
        return QVariant();
    if (role == Qt::ToolTipRole) {
        DBObjectItem* item = static_cast<DBObjectItem*>(itemByIndex(index));
        return item->objectUrl().toString();
    }
#endif
    return LStandardTreeModel::data(index, role);
}
