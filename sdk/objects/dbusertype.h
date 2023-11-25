#ifndef DBUSERTYPE_H
#define DBUSERTYPE_H

#include <QObject>
#include "dbobjectitem.h"

class DBUserType : public DBObjectItem
{
  Q_OBJECT
public:
  DBUserType();

  // DBObjectItem interface
public:
  virtual bool reloadChildren() override;
  virtual int type() const override;
};

#endif // DBUSERTYPE_H
