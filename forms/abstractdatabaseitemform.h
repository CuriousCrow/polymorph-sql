#ifndef ABSTRACTDATABASEITEMFORM_H
#define ABSTRACTDATABASEITEMFORM_H

#include <QDialog>
#include "dbms/qdbobjectitem.h"

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

  QDBObjectItem *objItem() const;
  void setObjItem(QDBObjectItem *objItem);

  virtual void objectToForm() = 0;
  virtual void formToObject() = 0;
protected:
  QDBObjectItem* _objItem;
private:
  UserAction _userAction;
};


#endif // ABSTRACTDATABASEITEMFORM_H
