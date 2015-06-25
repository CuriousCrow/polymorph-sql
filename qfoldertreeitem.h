#ifndef QFOLDERTREEITEM_H
#define QFOLDERTREEITEM_H

#include "qdbobjectitem.h"

class QFolderTreeItem : public QDBObjectItem
{
public:
  QFolderTreeItem(QString caption, QObject* parent = 0);
  ~QFolderTreeItem();

  // LAbstractTreeItem interface
public:
  virtual int colCount();
  virtual QVariant colData(int column, int role);

  // QDBObjectItem interface
public:
  virtual bool loadChildren();
  virtual int type();
};

#endif // QFOLDERTREEITEM_H
