#include "abstractdatabaseitemform.h"
#include <QMessageBox>
#include "../dbms/appconst.h"


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

void AbstractDatabaseEditForm::tryUserAction()
{
  ActionResult res;
  formToObject();

  if (userAction() == AbstractDatabaseEditForm::Create) {
    res = _objItem->insertMe();
  }
  if (res.isSuccess())
    accept();
  else {
    QMessageBox::warning(this, TITLE_ERROR, "Operation failed\r\n" + res.description());
  }
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
