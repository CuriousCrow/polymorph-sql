#ifndef BASEUSERCONTEXT_H
#define BASEUSERCONTEXT_H

#include "abstractusercontext.h"
#include "objects/dbobjectitem.h"
#include <QObject>

class BaseUserContext : public AbstractUserContext
{
    Q_OBJECT
public:
    BaseUserContext(QObject *parent = nullptr);
    DBObjectItem::ItemType type() const;

    DBObjectItem* currentItem();
public slots:
    void setCurrentItem(DBObjectItem* item);
protected:
    DBObjectItem* _currentItem;

};

#endif // BASEUSERCONTEXT_H
