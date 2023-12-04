#ifndef BASEUSERCONTEXT_H
#define BASEUSERCONTEXT_H

#include <QObject>
#include "abstractusercontext.h"
#include "objects/dbobjectitem.h"

class BaseUserContext : public AbstractUserContext
{
    Q_OBJECT
public:
    BaseUserContext(QObject *parent = nullptr);
    DBObjectItem::ItemType type() const;
    bool isEditable();
    bool hasCurItem();
    bool hasChildren();

    DBObjectItem* currentItem();
public slots:
    void setCurrentItem(DBObjectItem* item);
protected:
    DBObjectItem* _currentItem;

};

#endif // BASEUSERCONTEXT_H
