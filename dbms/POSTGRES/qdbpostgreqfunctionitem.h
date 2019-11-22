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
  virtual bool refresh() override;
  virtual bool insertMe() override;
  virtual bool updateMe() override;
  virtual bool deleteMe() override;
};

#endif // QDBPOSTGREQFUNCTIONITEM_H
