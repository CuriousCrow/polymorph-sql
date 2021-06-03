#ifndef POSTGRESPRIMARYKEY_H
#define POSTGRESPRIMARYKEY_H

#include <QObject>
#include "sdk/objects/dbprimarykey.h"

class PostgresPrimaryKey : public DBPrimaryKey
{
  Q_OBJECT
public:
  PostgresPrimaryKey(QString caption, QObject* parent = nullptr);

  // DBObjectItem interface
public:
  virtual bool refresh() Q_DECL_OVERRIDE;
};

#endif // POSTGRESPRIMARYKEY_H
