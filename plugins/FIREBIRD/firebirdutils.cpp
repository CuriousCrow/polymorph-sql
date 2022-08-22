#include "firebirdutils.h"

Utils::Utils()
{
}

QString Utils::typeFromCode(int code)
{
  switch (code) {
  case 261:
    return "BLOB";
  case 14:
    return "CHAR";
  case 40:
    return "CSTRING";
  case 11:
    return "DFLOAT";
  case 27:
    return "DOUBLE";
  case 10:
    return "FLOAT";
  case 16:
    return "BIGINT";
  case 8:
    return "INTEGER";
  case 9:
    return "QUAD";
  case 7:
    return "SMALLINT";
  case 12:
    return "DATE";
  case 13:
    return "TIME";
  case 35:
    return "TIMESTAMP";
  case 37:
    return "VARCHAR";
  default:
    return "UNKNOWN";
  }
}
