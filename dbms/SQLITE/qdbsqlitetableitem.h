#ifndef QDBSQLITETABLEITEM_H
#define QDBSQLITETABLEITEM_H

#include "../qdbtableitem.h"

class QDBSqliteTableItem : public QDBTableItem
{
public:
    QDBSqliteTableItem(QString caption, QObject* parent = nullptr);
    virtual void reloadColumnsModel();
    // QDBObjectItem interface
public:
    virtual bool insertMe();
    virtual bool updateMe();
private:
    QString createTableQuery(QString table);
};

#endif // QDBSQLITETABLEITEM_H
