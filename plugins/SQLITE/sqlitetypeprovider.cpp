#include "sqlitetypeprovider.h"

SqliteTypeProvider::SqliteTypeProvider()
{
  _types.append(new StringDBType("TEXT", "Text"));
  _types.append(new IntegerDBType("INTEGER", "Integer"));
  _types.append(new FloatDBType("FLOAT", "Float"));
  _types.append(new BlobDBType("BLOB", "BLOB"));
}
