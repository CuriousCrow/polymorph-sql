#ifndef MYSQLFOREIGNKEY_H
#define MYSQLFOREIGNKEY_H

#include "objects/dbforeignkey.h"
#include <QObject>

class MysqlForeignKey : public DBForeignKey
{
  Q_OBJECT
public:
  Q_INVOKABLE MysqlForeignKey();

  // DBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // MYSQLFOREIGNKEY_H
