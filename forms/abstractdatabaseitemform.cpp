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

AbstractDatabaseEditForm::UserAction AbstractDatabaseEditForm::userAction() const
{
  return _userAction;
}

void AbstractDatabaseEditForm::setUserAction(const UserAction &userAction)
{
  _userAction = userAction;
  emit userActionChanged();
}
