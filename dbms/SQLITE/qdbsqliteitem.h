#ifndef QDBSQLITEITEM_H
#define QDBSQLITEITEM_H

#include "../qdbdatabaseitem.h"

class QDBSqliteItem : public QDBDatabaseItem
{
    Q_OBJECT
public:
    QDBSqliteItem(QString caption);

public:
    virtual bool loadChildren() override;
    virtual QDBTableItem* createNewTableItem(QString caption, QObject* parent = nullptr) override;
    // QDBDatabaseItem interface
protected:
    virtual QString getViewListSql() override;
    virtual QString getSequenceListSql() override;
    virtual QString getTriggerListSql() override;
    virtual QString getProcedureListSql() override;
};

#endif // QDBSQLITEITEM_H
