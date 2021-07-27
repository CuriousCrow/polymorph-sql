#include "baseusercontext.h"



BaseUserContext::BaseUserContext(QObject *parent) : AbstractUserContext(parent)
{

}

DBObjectItem::ItemType BaseUserContext::type() const
{
    return _currentItem ? (DBObjectItem::ItemType(_currentItem->type())) : DBObjectItem::UnknownType;
}

DBObjectItem *BaseUserContext::currentItem()
{
    return _currentItem;
}

void BaseUserContext::setCurrentItem(DBObjectItem *item)
{
    if (_currentItem == item)
        return;
    _currentItem = item;
    emit contextChanged();
}
