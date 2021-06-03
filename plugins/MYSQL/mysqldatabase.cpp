#include "mysqldatabase.h"
#include "mysqltable.h"
#include "sdk/objects/foldertreeitem.h"
#include "sdk/objects/appconst.h"

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

QString MysqlDatabase::getAllObjectListSql() const
{
  return "SELECT table_name, 'table' FROM information_schema.tables "
         "WHERE table_schema = 'test' AND table_type = 'BASE TABLE' "
         "UNION ALL "
         "SELECT table_name, 'view' FROM information_schema.views "
         "UNION ALL "
         "SELECT routine_name, 'procedure' FROM information_schema.routines "
         "WHERE ROUTINE_TYPE='PROCEDURE' ";
}
