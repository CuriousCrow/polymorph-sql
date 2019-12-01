#ifndef DBSQLITEITEM_H
#define DBSQLITEITEM_H

#include "../dbdatabaseitem.h"

class DBSqliteItem : public DBDatabaseItem
{
    Q_OBJECT
public:
    DBSqliteItem(QString caption);

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

#endif // DBSQLITEITEM_H
