#ifndef QDBSQLITEITEM_H
#define QDBSQLITEITEM_H

#include "../qdbdatabaseitem.h"

class QDBSqliteItem : public QDBDatabaseItem
{
    Q_OBJECT
public:
    QDBSqliteItem(QString caption, QObject* parent = nullptr);

public:
    virtual bool loadChildren();
    virtual QDBTableItem* createNewTableItem(QString caption, QObject* parent = nullptr);
    // QDBDatabaseItem interface
protected:
    virtual QString getViewListSql();
    virtual QString getSequenceListSql();
    virtual QString getTriggerListSql();
    virtual QString getProcedureListSql();
};

#endif // QDBSQLITEITEM_H
