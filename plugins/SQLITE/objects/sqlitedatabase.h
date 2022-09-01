#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include "objects/dbdatabaseitem.h"

/** Sqlite database item */
class SqliteDatabase : public DBDatabaseItem
{
    Q_OBJECT
public:
    Q_INVOKABLE SqliteDatabase();
public:
    ActionResult insertMe() Q_DECL_OVERRIDE;
    virtual bool reloadChildren() Q_DECL_OVERRIDE;
    virtual QString getAllObjectListSql() const Q_DECL_OVERRIDE;
};

#endif // SQLITEDATABASE_H
