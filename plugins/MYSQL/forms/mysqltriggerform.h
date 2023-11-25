#ifndef MYSQLTRIGGERFORM_H
#define MYSQLTRIGGERFORM_H

#include "core/datastore.h"
#include "core/dependencycontainer.h"
#include "forms/abstractdatabaseitemform.h"

namespace Ui {
class MysqlTriggerForm;
}

class MysqlTriggerForm : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  Q_INVOKABLE MysqlTriggerForm();
  ~MysqlTriggerForm();

  INJECT(DataStore*, ds)

private:
  Ui::MysqlTriggerForm *ui;

  // AbstractDatabaseEditForm interface
public:
  virtual void objectToForm() override;
  virtual void formToObject() override;
private slots:
  void on_btnApply_clicked();
  void on_btnCancel_clicked();
  void onUserActionChanged();
  void on_edtName_textChanged(const QString &text);
};

#endif // MYSQLTRIGGERFORM_H
