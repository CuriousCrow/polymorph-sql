#ifndef POSTGRESPRIMARYKEY_H
#define POSTGRESPRIMARYKEY_H

#include <QObject>
#include "objects/dbprimarykey.h"

class PostgresPrimaryKey : public DBPrimaryKey
{
  Q_OBJECT
public:
  Q_INVOKABLE PostgresPrimaryKey();

  // DBObjectItem interface
public:
  virtual bool refresh() Q_DECL_OVERRIDE;
};

#endif // POSTGRESPRIMARYKEY_H
