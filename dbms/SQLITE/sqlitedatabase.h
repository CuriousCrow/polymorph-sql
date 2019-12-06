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
    virtual DBTableItem* createNewTableItem(QString caption, QObject* parent = nullptr) override;
    // DBDatabaseItem interface
protected:
    virtual QString getViewListSql() override;
    virtual QString getSequenceListSql() override;
    virtual QString getTriggerListSql() override;
    virtual QString getProcedureListSql() override;

    // DBDatabaseItem interface
protected:
    virtual void loadSequenceItems(DBObjectItem *parentItem) override;
};

#endif // SQLITEDATABASE_H
