#include "firebirdtypeprovider.h"

FirebirdTypeProvider::FirebirdTypeProvider() : BaseTypeProvider()
{
  _types.append(new StringDBType("VARCHAR", "Varchar"));
  _types.append(new IntegerDBType("INTEGER", "Integer"));
  _types.append(new IntegerDBType("SMALLINT", "SmallInt"));
  _types.append(new IntegerDBType("BIGINT", "BigInt"));
}
