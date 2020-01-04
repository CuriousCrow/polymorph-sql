#include "firebirddatabase.h"
#include "firebirdtable.h"
#include "../appconst.h"

FirebirdDatabase::FirebirdDatabase(QString caption)
  : DBDatabaseItem(caption)
{
  setFieldValue(F_DRIVER_NAME, DRIVER_FIREBIRD);
}
