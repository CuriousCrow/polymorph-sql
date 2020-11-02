#ifndef DBSQLITETABLEITEM_H
#define DBSQLITETABLEITEM_H

#include "../dbtableitem.h"

class SqliteTableItem : public DBTableItem
{
public:
    SqliteTableItem(QString caption, QObject* parent = nullptr);
    virtual ~SqliteTableItem() override;
    virtual void reloadColumnsModel() Q_DECL_OVERRIDE;
    // DBObjectItem interface
public:
    virtual ActionResult insertMe() Q_DECL_OVERRIDE;
    virtual ActionResult updateMe() Q_DECL_OVERRIDE;
private:
    QString createTableQuery(QString table) const;
};

#endif // DBSQLITETABLEITEM_H
