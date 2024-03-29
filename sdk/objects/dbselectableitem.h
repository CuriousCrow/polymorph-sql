#ifndef DBSELECTABLEITEM_H
#define DBSELECTABLEITEM_H

#include <QObject>
#include "dbobjectitem.h"

class DBSelectableItem : public DBObjectItem
{
    Q_OBJECT
public:
    DBSelectableItem(QString caption, QObject* parent = nullptr);
    // LAbstractTreeItem interface
public:
    virtual int colCount() const Q_DECL_OVERRIDE;
    virtual QVariant colData(int column, int role) const Q_DECL_OVERRIDE;
public:
    virtual bool reloadChildren() Q_DECL_OVERRIDE;
protected:
    virtual QString fillSqlPatternWithFields(QString pattern) const Q_DECL_OVERRIDE;
};

#endif // DBSELECTABLEITEM_H
