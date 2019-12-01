#ifndef DBSQLITETABLEITEM_H
#define DBSQLITETABLEITEM_H

#include "../dbtableitem.h"

class DBSqliteTableItem : public DBTableItem
{
public:
    DBSqliteTableItem(QString caption, QObject* parent = nullptr);
    virtual void reloadColumnsModel() override;
    // DBObjectItem interface
public:
    virtual ActionResult insertMe() override;
    virtual ActionResult updateMe() override;
private:
    QString createTableQuery(QString table);
};

#endif // DBSQLITETABLEITEM_H