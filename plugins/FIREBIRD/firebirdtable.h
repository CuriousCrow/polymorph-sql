#ifndef FIREBIRDTABLE_H
#define FIREBIRDTABLE_H

#include "sdk/objects/dbtableitem.h"

class FirebirdTable : public DBTableItem
{
  Q_OBJECT
public:
  FirebirdTable(QString caption, QObject* parent = nullptr);
  virtual ~FirebirdTable() override;
  // DBTableItem interface
public:
  virtual void reloadColumnsModel() Q_DECL_OVERRIDE;
};

#endif // FIREBIRDTABLE_H
