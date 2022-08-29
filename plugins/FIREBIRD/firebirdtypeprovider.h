#ifndef FIREBIRDTYPEPROVIDER_H
#define FIREBIRDTYPEPROVIDER_H

#include "objects/typeprovider.h"
#include "core/datastore.h"
#include "core/lknowledgebase.h"
#include <QObject>

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
