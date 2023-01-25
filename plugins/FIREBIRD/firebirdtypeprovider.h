#ifndef FIREBIRDTYPEPROVIDER_H
#define FIREBIRDTYPEPROVIDER_H

#include "objects/typeprovider.h"
#include "core/datastore.h"
#include "core/lknowledgebase.h"
#include <QObject>

class FirebirdDomainType : public BaseDBType
{
public:
  FirebirdDomainType(QString name, QString title = "");
  // DBType interface
public:
  virtual bool isUserType() const override;
  virtual QString valueToSql(const QVariant &value) override;
};

class FirebirdTypeProvider : public BaseTypeProvider
{
  Q_OBJECT
public:
  Q_INVOKABLE FirebirdTypeProvider();
  INJECT(DataStore*, ds)
protected:
  void reload() Q_DECL_OVERRIDE;
};

#endif // FIREBIRDTYPEPROVIDER_H
