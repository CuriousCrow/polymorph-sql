#ifndef FIREBIRDFOREIGNKEY_H
#define FIREBIRDFOREIGNKEY_H

#include "objects/dbforeignkey.h"
#include <QObject>

class FirebirdForeignKey : public DBForeignKey
{
  Q_OBJECT
public:
  Q_INVOKABLE FirebirdForeignKey();

  // DBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // FIREBIRDFOREIGNKEY_H
