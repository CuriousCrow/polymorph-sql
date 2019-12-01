#ifndef QDBSQLITETABLEITEM_H
#define QDBSQLITETABLEITEM_H

#include "../qdbtableitem.h"

class DBSqliteTableItem : public DBTableItem
{
public:
    DBSqliteTableItem(QString caption, QObject* parent = nullptr);
    virtual void reloadColumnsModel() override;
    // QDBObjectItem interface
public:
    virtual ActionResult insertMe() override;
    virtual ActionResult updateMe() override;
private:
    QString createTableQuery(QString table);
};

#endif // QDBSQLITETABLEITEM_H
