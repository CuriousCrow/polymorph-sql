#include "mysqldatabase.h"

#include "mysqltable.h"
#include "objects/appconst.h"
#include "objects/foldertreeitem.h"

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
  QString pattern = "SELECT table_name as \"name\", 'table' as \"type\" FROM information_schema.tables "
         "WHERE table_schema = '#databaseName#' AND table_type = 'BASE TABLE' "
         "UNION ALL "
         "SELECT table_name, 'view' FROM information_schema.views "
         "WHERE table_schema = '#databaseName#' "
         "UNION ALL "
         "SELECT routine_name, 'procedure' FROM information_schema.routines "
         "WHERE ROUTINE_SCHEMA = '#databaseName#' AND ROUTINE_TYPE='PROCEDURE' ";
  return fillSqlPatternWithFields(pattern);
}
