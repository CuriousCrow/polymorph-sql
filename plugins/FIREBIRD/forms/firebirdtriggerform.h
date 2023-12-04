#ifndef FIREBIRDTRIGGERFORM_H
#define FIREBIRDTRIGGERFORM_H

#include "core/datastore.h"
#include "core/dependencycontainer.h"
#include "forms/abstractdatabaseitemform.h"

namespace Ui {
class FirebirdTriggerForm;
}

class FirebirdTriggerForm : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  Q_INVOKABLE FirebirdTriggerForm();
  ~FirebirdTriggerForm();

  INJECT(DataStore*, ds)

private:
  Ui::FirebirdTriggerForm *ui;

  // AbstractDatabaseEditForm interface
public:
  virtual void objectToForm() override;
  virtual void formToObject() override;

private slots:
  void on_btnApply_clicked();
  void on_btnCancel_clicked();

  void onUserActionChanged();
};

#endif // FIREBIRDTRIGGERFORM_H
