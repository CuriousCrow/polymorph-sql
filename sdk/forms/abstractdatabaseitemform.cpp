#include "abstractdatabaseitemform.h"
#include <QMessageBox>
#include "objects/appconst.h"


AbstractDatabaseEditForm::AbstractDatabaseEditForm(QWidget *parent, Qt::WindowFlags f)
  : NotifiableDialog(parent, f)
{
    setWindowModality(Qt::ApplicationModal);
}

DBObjectItem *AbstractDatabaseEditForm::objItem() const
{
  return _objItem;
}

void AbstractDatabaseEditForm::setObjItem(DBObjectItem *objItem)
{
  _objItem = objItem;
}

void AbstractDatabaseEditForm::tryUserAction()
{
  ActionResult res;
  formToObject();

  //TODO: Automatically disable "Apply" button if unmodified
  if ((userAction()==AbstractDatabaseEditForm::Edit) && !_objItem->isModified())
    reject();

  QStringList validationResult = _objItem->validate();
  if (!validationResult.isEmpty()) {
    res = ActionResult(ERR_VALIDATION_ERROR, validationResult.first());
  }
  else if (userAction() == AbstractDatabaseEditForm::Create) {
    res = _objItem->insertMe();
  }
  else if (userAction() == AbstractDatabaseEditForm::Edit) {
    res = _objItem->updateMe();
    if (res.isSuccess() && _objItem->fieldModified(F_CAPTION)) {
      _objItem->updateUrl();
    }
  }
  if (res.isSuccess()) {
    _objItem->submit();
    accept();
  }
  else if (res.resCode() == ERR_NOT_IMPLEMENTED) {
    QMessageBox::warning(this, TITLE_ERROR, tr("Feature not implemented yet"));
  }
  else {
    QMessageBox::warning(this, TITLE_ERROR, tr("Operation failed\r\n") + res.description());
  }
}

void AbstractDatabaseEditForm::cancel()
{
  _objItem->revert();
  reject();
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
