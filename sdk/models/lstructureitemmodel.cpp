#include "lstructureitemmodel.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include "objects/appurl.h"

#define TREEMODEL_DEBUG

LStructureItemModel::LStructureItemModel(QObject *parent):
  LStandardTreeModel(parent)
{
  connect(this, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
          SLOT(onAboutToBeRemoved(QModelIndex,int,int)));
}

LStructureItemModel::~LStructureItemModel()
{
}

void LStructureItemModel::appendItem(DBObjectItem *item, DBObjectItem *parent)
{
  addItem(item, parent);
  if (parent)
    item->setParentUrl(parent->objectUrl());
  else
    item->setParentUrl(AppUrl());
}

void LStructureItemModel::appendItem(DBObjectItem *item, QModelIndex parent)
{
  addItem(item, parent);
  if (parent.isValid()) {
    DBObjectItem* parentItem = itemByIdx(parent);
    Q_ASSERT(parentItem);
    item->setParentUrl(parentItem->objectUrl());
  }
}

QModelIndex LStructureItemModel::indexByUrl(const AppUrl &url)
{
  return indexByName(url.toString());
}

DBObjectItem *LStructureItemModel::itemByUrl(const AppUrl &url)
{
    return static_cast<DBObjectItem*>(itemByName(url.toString()));
}

DBObjectItem *LStructureItemModel::itemByIdx(const QModelIndex &idx)
{
    return static_cast<DBObjectItem*>(itemByIndex(idx));
}

bool LStructureItemModel::deleteChildren(QModelIndex parent)
{
    return removeRows(0, rowCount(parent), parent);
}

bool LStructureItemModel::deleteChildren(DBObjectItem *parentItem)
{
    return deleteChildren(indexByItem(parentItem));
}

void LStructureItemModel::onAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
  for (int row=first; row<last; row++){
    DBObjectItem* item = static_cast<DBObjectItem*>(itemByIndex(index(row, 0, parent)));
    emit itemAboutToBeRemoved(item->objectUrl().toString());
  }
}


Qt::ItemFlags LStructureItemModel::flags(const QModelIndex &index) const
{
  DBObjectItem* item = static_cast<DBObjectItem*>(itemByIndex(index));
  if ((item->type() == DBObjectItem::Database)
      && item->children().count() > 0){
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QVariant LStructureItemModel::data(const QModelIndex &index, int role) const
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
