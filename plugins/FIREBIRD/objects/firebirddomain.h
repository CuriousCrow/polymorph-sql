#ifndef FIREBIRDDOMAIN_H
#define FIREBIRDDOMAIN_H

#include "objects/dbusertype.h"
#include <QObject>

class FirebirdDomain : public DBUserType
{
  Q_OBJECT
public:
  Q_INVOKABLE FirebirdDomain();

  // DBObjectItem interface
public:
  virtual QString toDDL() const override;
  virtual ActionResult insertMe() override;
  virtual ActionResult deleteMe() override;
  virtual bool refresh() override;

  // LAbstractTreeItem interface
public:
  virtual int colCount() const override;
  virtual QVariant colData(int column, int role) const override;
};

#endif // FIREBIRDDOMAIN_H
