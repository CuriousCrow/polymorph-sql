#ifndef QDBSEQUENCEITEM_H
#define QDBSEQUENCEITEM_H

#include "qdbobjectitem.h"

class QDBSequenceItem : public QDBObjectItem
{
  Q_OBJECT
public:
  QDBSequenceItem(QString caption, QObject* parent = 0);
  ~QDBSequenceItem();

  // LAbstractTreeItem interface
public:
  virtual int colCount();
  virtual QVariant colData(int column, int role);

  // QDBObjectItem interface
public:
  virtual bool loadChildren();
  virtual int type();
};

#endif // QDBSEQUENCEITEM_H
