#ifndef POSTGRESPRIMARYKEY_H
#define POSTGRESPRIMARYKEY_H

#include <QObject>
#include "../dbprimarykey.h"

class PostgresPrimaryKey : public DBPrimaryKey
{
  Q_OBJECT
public:
  PostgresPrimaryKey(QString caption, QObject* parent = nullptr);

  // DBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // POSTGRESPRIMARYKEY_H
