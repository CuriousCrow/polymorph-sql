#include "abstractdatabaseitemform.h"


AbstractDatabaseEditForm::AbstractDatabaseEditForm(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
}

QDBObjectItem *AbstractDatabaseEditForm::objItem() const
{
    return _objItem;
}

void AbstractDatabaseEditForm::setObjItem(QDBObjectItem *objItem)
{
    _objItem = objItem;
}
