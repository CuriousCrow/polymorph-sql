#ifndef ABSTRACTDATABASEITEMFORM_H
#define ABSTRACTDATABASEITEMFORM_H

#include <QDialog>
#include "dbms/dbobjectitem.h"

class AbstractDatabaseEditForm : public QDialog
{
  Q_OBJECT
public:
  enum UserAction {
    Create,
    Edit,
    Drop
  };

  AbstractDatabaseEditForm(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

  UserAction userAction() const;
  void setUserAction(const UserAction &userAction);

  DBObjectItem *objItem() const;
  void setObjItem(DBObjectItem *objItem);

  virtual void objectToForm() = 0;
  virtual void formToObject() = 0;
signals:
  void userActionChanged();
protected:
  DBObjectItem* _objItem;
  virtual void tryUserAction();
private:
  UserAction _userAction;
};


#endif // ABSTRACTDATABASEITEMFORM_H
