#ifndef FIREBIRDPRIMARYKEY_H
#define FIREBIRDPRIMARYKEY_H

#include "objects/dbprimarykey.h"
#include <QObject>
#include <QString>

class FirebirdPrimaryKey : public DBPrimaryKey
{
  Q_OBJECT
public:
  Q_INVOKABLE FirebirdPrimaryKey();

  // DBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // FIREBIRDPRIMARYKEY_H
