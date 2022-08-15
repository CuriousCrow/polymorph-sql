#ifndef MYSQLVIEW_H
#define MYSQLVIEW_H

#include "objects/dbviewitem.h"
#include <QObject>

class MysqlView : public DBViewItem
{
  Q_OBJECT
public:
  Q_INVOKABLE MysqlView();

  // DBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // MYSQLVIEW_H
