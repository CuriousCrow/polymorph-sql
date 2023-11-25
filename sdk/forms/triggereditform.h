#ifndef TRIGGEREDITFORM_H
#define TRIGGEREDITFORM_H

#include <QDialog>
#include "abstractdatabaseitemform.h"
#include "core/datastore.h"
#include "core/dependencycontainer.h"

namespace Ui {
class TriggerEditForm;
}

class TriggerEditForm : public AbstractDatabaseEditForm
{
  Q_OBJECT
public:
  Q_INVOKABLE TriggerEditForm();
  ~TriggerEditForm();

  INJECT(DataStore*, ds)

private:
  Ui::TriggerEditForm *ui;

  // AbstractDatabaseEditForm interface
public:
  void objectToForm();
  void formToObject();
private slots:
  void on_btnApply_clicked();
  void on_btnCancel_clicked();
  void onUserActionChanged();
};

#endif // TRIGGEREDITFORM_H
