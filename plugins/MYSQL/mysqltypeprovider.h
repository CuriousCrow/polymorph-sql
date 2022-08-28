#ifndef MYSQLTYPEPROVIDER_H
#define MYSQLTYPEPROVIDER_H

#include <QObject>
#include "objects/typeprovider.h"

class MysqlTypeProvider : public BaseTypeProvider
{
  Q_OBJECT
public:
  Q_INVOKABLE MysqlTypeProvider();
};

#endif // MYSQLTYPEPROVIDER_H
