#ifndef QDBPOSTGREQFUNCTIONITEM_H
#define QDBPOSTGREQFUNCTIONITEM_H

#include <QObject>
#include "../qdbprocedureitem.h"

class QDBPostgreqFunctionItem : public QDBProcedureItem
{
  Q_OBJECT
public:
  QDBPostgreqFunctionItem(QString caption, QObject* parent = nullptr);

  // QDBObjectItem interface
public:
  bool refresh();
  bool insertMe();
  bool updateMe();
};

#endif // QDBPOSTGREQFUNCTIONITEM_H
