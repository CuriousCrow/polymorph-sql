#ifndef FIREBIRDTYPEPROVIDER_H
#define FIREBIRDTYPEPROVIDER_H

#include "objects/typeprovider.h"
#include <QObject>

class FirebirdTypeProvider : public BaseTypeProvider
{
  Q_OBJECT
public:
  Q_INVOKABLE FirebirdTypeProvider();
};

#endif // FIREBIRDTYPEPROVIDER_H
