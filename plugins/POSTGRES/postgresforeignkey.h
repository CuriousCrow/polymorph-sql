#ifndef POSTGRESFOREIGNKEY_H
#define POSTGRESFOREIGNKEY_H

#include <QObject>
#include "sdk/objects/dbforeignkey.h"

class PostgresForeignKey : public DBForeignKey
{
  Q_OBJECT
public:
  Q_INVOKABLE PostgresForeignKey();

  // DBObjectItem interface
public:
  virtual bool refresh() Q_DECL_OVERRIDE;
};

#endif // POSTGRESFOREIGNKEY_H
