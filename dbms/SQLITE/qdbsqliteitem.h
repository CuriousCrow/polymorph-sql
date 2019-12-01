#ifndef QDBSQLITEITEM_H
#define QDBSQLITEITEM_H

#include "../qdbdatabaseitem.h"

class DBSqliteItem : public DBDatabaseItem
{
    Q_OBJECT
public:
    DBSqliteItem(QString caption);

public:
    virtual bool reloadChildren() override;
    virtual DBTableItem* createNewTableItem(QString caption, QObject* parent = nullptr) override;
    // QDBDatabaseItem interface
protected:
    virtual QString getViewListSql() override;
    virtual QString getSequenceListSql() override;
    virtual QString getTriggerListSql() override;
    virtual QString getProcedureListSql() override;

    // QDBDatabaseItem interface
protected:
    virtual void loadSequenceItems(DBObjectItem *parentItem) override;
};

#endif // QDBSQLITEITEM_H
