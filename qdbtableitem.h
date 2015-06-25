#ifndef QDBTABLEITEM_H
#define QDBTABLEITEM_H

#include "qdbobjectitem.h"

class QDBTableItem : public QDBObjectItem
{
public:
  QDBTableItem(QString caption, QObject* parent = 0);
  ~QDBTableItem();

  // QDBObjectItem interface
public:
  virtual bool loadChildren();
  virtual QUrl objectUrl();
  virtual int type();

  // LAbstractTreeItem interface
public:
  virtual int colCount();
  virtual QVariant colData(int column, int role);
};

#endif // QDBTABLEITEM_H
