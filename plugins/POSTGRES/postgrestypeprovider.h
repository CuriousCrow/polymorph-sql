#ifndef POSTGRESTYPEPROVIDER_H
#define POSTGRESTYPEPROVIDER_H

#include <QObject>
#include "objects/typeprovider.h"

class PostgresTypeProvider : public BaseTypeProvider
{
  Q_OBJECT
public:
  Q_INVOKABLE PostgresTypeProvider();
};

#endif // POSTGRESTYPEPROVIDER_H
