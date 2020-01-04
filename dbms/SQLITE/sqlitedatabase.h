#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include "../dbdatabaseitem.h"

class SqliteDatabase : public DBDatabaseItem
{
    Q_OBJECT
public:
    SqliteDatabase(QString caption);
public:
    virtual bool reloadChildren() override;
};

#endif // SQLITEDATABASE_H
