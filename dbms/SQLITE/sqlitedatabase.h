#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include "../dbdatabaseitem.h"

class SqliteDatabase : public DBDatabaseItem
{
    Q_OBJECT
public:
    SqliteDatabase(QString caption);
public:
    virtual bool reloadChildren() Q_DECL_OVERRIDE;
    virtual QString getAllObjectListSql() Q_DECL_OVERRIDE;
};

#endif // SQLITEDATABASE_H
