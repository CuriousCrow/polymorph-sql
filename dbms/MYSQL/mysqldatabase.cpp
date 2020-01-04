#include "mysqldatabase.h"
#include "mysqltable.h"
#include "../foldertreeitem.h"
#include "../appconst.h"


MysqlDatabase::MysqlDatabase(QString caption)
  : DBDatabaseItem(caption)
{
  setFieldValue(F_DRIVER_NAME, DRIVER_MYSQL);
}

MysqlDatabase::~MysqlDatabase()
{
}

bool MysqlDatabase::reloadChildren()
{
  return true;
}
