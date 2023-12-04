#ifndef MYSQLPRIMARYKEY_H
#define MYSQLPRIMARYKEY_H

#include <QObject>
#include "objects/dbprimarykey.h"


class MysqlPrimaryKey : public DBPrimaryKey
{
  Q_OBJECT
public:
  Q_INVOKABLE MysqlPrimaryKey();

  // DBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // MYSQLPRIMARYKEY_H
