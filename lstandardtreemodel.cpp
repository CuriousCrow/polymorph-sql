#include "lstandardtreemodel.h"
#include <QDebug>
#include <QColor>

LAbstractTreeItem::LAbstractTreeItem(QString name, QObject *parent) : QObject(parent)
{
  setObjectName(name);
//  qDebug() << "item" << this << "created";
}

LAbstractTreeItem::~LAbstractTreeItem()
{
//  qDebug() << "item" << this << "destroyed";
}

bool LAbstractTreeItem::hasChildren()
{
  return children().count() > 0;
}

int LAbstractTreeItem::colCount()
{
  return 1;
}

QVariant LAbstractTreeItem::colData(int row, int role)
{
  switch (role) {
  case Qt::DisplayRole:
    switch (row) {
    case 0:
      return objectName();
    default:
      return QVariant();
    }
  case Qt::BackgroundColorRole:
    return QVariant();
  default:
    return QVariant();
  }
}


LStandardTreeModel::LStandardTreeModel(QObject *parent):
  QAbstractItemModel(parent)
{
}

LStandardTreeModel::~LStandardTreeModel()
{
}

void LStandardTreeModel::addItem(LAbstractTreeItem *item, LAbstractTreeItem *parent)
{  
  addItem(item, indexByItem(parent));
}

void LStandardTreeModel::addItem(LAbstractTreeItem *item, QModelIndex parent)
{
  int newRowIndex = rowCount(parent);
  beginInsertRows(parent, newRowIndex, newRowIndex);

  if (parent.isValid()){
    item->setParent(itemByIndex(parent));
  }
  else {
    item->setParent(this);
  }
  endInsertRows();
}

LAbstractTreeItem *LStandardTreeModel::itemByIndex(QModelIndex index) const
{
  return static_cast<LAbstractTreeItem*>(index.internalPointer());
}

LAbstractTreeItem *LStandardTreeModel::itemByName(QString name) const
{
  return findChild<LAbstractTreeItem*>(name);
}

QModelIndex LStandardTreeModel::indexByItem(LAbstractTreeItem *item)
{
  if (!item || !findChild<LAbstractTreeItem*>(item->objectName()))
    return QModelIndex();

  QObject* parentObj = item->parent();
  int itemRow = parentObj->children().indexOf(item);
  return createIndex(itemRow, 0, item);
}

QModelIndex LStandardTreeModel::index(int row, int column, const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent))
    return QModelIndex();

  LAbstractTreeItem* childItem;

  if (!parent.isValid()){
    childItem = qobject_cast<LAbstractTreeItem*>(children().at(row));
  }
  else {
    LAbstractTreeItem* parentItem = itemByIndex(parent);
    childItem = qobject_cast<LAbstractTreeItem*>(parentItem->children().at(row));
  }
  if (childItem){
    return createIndex(row, column, childItem);
  }
  else {
    return QModelIndex();
  }
}

QModelIndex LStandardTreeModel::parent(const QModelIndex &child) const
{
  LAbstractTreeItem* childItem = itemByIndex(child);
  if (childItem->parent()->inherits("LAbstractTreeItem")){
    LAbstractTreeItem* parentItem = qobject_cast<LAbstractTreeItem*>(childItem->parent());
    QObject* grandParent = parentItem->parent();
    return createIndex(grandParent->children().indexOf(parentItem), 0, parentItem);
  }
  else {
    return QModelIndex();
  }
}

int LStandardTreeModel::rowCount(const QModelIndex &parent) const
{
  if (parent.isValid()){
    LAbstractTreeItem* parentItem = itemByIndex(parent);
    int childCount = parentItem->children().count();
    return childCount;
  }
  else {
    return children().count();
  }
}

int LStandardTreeModel::columnCount(const QModelIndex &parent) const
{
  LAbstractTreeItem* firstChildItem = nullptr;
  if (parent.isValid()){
    LAbstractTreeItem* parentItem = itemByIndex(parent);
    if (parentItem->children().isEmpty())
      return 1;
    firstChildItem = qobject_cast<LAbstractTreeItem*>(parentItem->children().at(0));
  }
  else {
    if (children().isEmpty())
      return 1;
    firstChildItem = qobject_cast<LAbstractTreeItem*>(children().at(0));
  }
  return firstChildItem->colCount();
}

bool LStandardTreeModel::hasChildren(const QModelIndex &parent) const
{
  return rowCount(parent) > 0;
}

QVariant LStandardTreeModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();
  return itemByIndex(index)->colData(index.column(), role);
}


bool LStandardTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (!index.isValid())
    return false;
  return itemByIndex(index)->setData(index.column(), value, role);
}

Qt::ItemFlags LStandardTreeModel::flags(const QModelIndex &index) const
{
  Q_UNUSED(index)
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}


bool LStandardTreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
  if (row < 0 || count <= 0)
    return false;
  //TODO: Here should be existance check of some sort
  QObject* parentObj = parent.isValid() ? itemByIndex(parent) : qobject_cast<QObject*>(this);

  beginRemoveRows(parent, row, row + count - 1);
  for (int i=0; i<count; i++){
    QObject* childItem = parentObj->children().at(row);
    childItem->setParent(nullptr);
    delete childItem;
  }
  endRemoveRows();
  return true;
}
