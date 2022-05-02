#ifndef DBSQLITETABLEITEM_H
#define DBSQLITETABLEITEM_H

#include "objects/dbtableitem.h"

/** SQLite table item */
class SqliteTableItem : public DBTableItem
{
    Q_OBJECT
public:
    Q_INVOKABLE SqliteTableItem();
    virtual ~SqliteTableItem() override;

    INJECT_INITIALIZE(SqlColumnModel*, _columnsModel, baseColumnModel)

    virtual void reloadColumnsModel() Q_DECL_OVERRIDE;
    // DBObjectItem interface
public:
    virtual ActionResult insertMe() Q_DECL_OVERRIDE;
    virtual ActionResult updateMe() Q_DECL_OVERRIDE;
private:
    QString createTableQuery(QString table) const;
};

#endif // DBSQLITETABLEITEM_H
