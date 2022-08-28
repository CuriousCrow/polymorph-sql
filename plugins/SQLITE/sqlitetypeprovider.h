#ifndef SQLITETYPEPROVIDER_H
#define SQLITETYPEPROVIDER_H

#include <QObject>
#include "objects/typeprovider.h"

class SqliteTypeProvider : public BaseTypeProvider
{
  Q_OBJECT
public:
  Q_INVOKABLE SqliteTypeProvider();
};

#endif // SQLITETYPEPROVIDER_H
