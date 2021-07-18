#include "mysqldatabase.h"
#include "mysqltable.h"
#include "objects/foldertreeitem.h"
#include "objects/appconst.h"

#define MYSQL_PORT 3306

MysqlDatabase::MysqlDatabase()
  : DBDatabaseItem("")
{
  setFieldValue(F_DRIVER_NAME, DRIVER_MYSQL);
  setFieldValue(F_PORT, MYSQL_PORT);
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
