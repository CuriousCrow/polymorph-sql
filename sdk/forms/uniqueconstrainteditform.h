#ifndef UNIQUECONSTRAINTEDITFORM_H
#define UNIQUECONSTRAINTEDITFORM_H

#include <QDialog>
#include "abstractdatabaseitemform.h"
#include "core/datastore.h"
#include "core/dependencycontainer.h"

namespace Ui {
class UniqueConstraintEditForm;
}

class UniqueConstraintEditForm : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  Q_INVOKABLE UniqueConstraintEditForm(QWidget *parent = nullptr);
  ~UniqueConstraintEditForm() override;

  INJECT(DataStore*, ds)
private:
  Ui::UniqueConstraintEditForm *ui;

  // AbstractDatabaseEditForm interface
public:
  virtual void objectToForm() override;
  virtual void formToObject() override;
private slots:
  void on_btnApply_clicked();
  void on_btnCancel_clicked();
  void onUserActionChanged();
};

#endif // UNIQUECONSTRAINTEDITFORM_H
