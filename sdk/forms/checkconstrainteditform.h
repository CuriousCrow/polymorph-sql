#ifndef CHECKCONSTRAINTEDITFORM_H
#define CHECKCONSTRAINTEDITFORM_H

#include <QDialog>
#include "abstractdatabaseitemform.h"

namespace Ui {
class CheckConstraintEditForm;
}

class CheckConstraintEditForm : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  Q_INVOKABLE CheckConstraintEditForm(QWidget *parent = nullptr);
  ~CheckConstraintEditForm() override;

private slots:
  void on_btnApply_clicked();

  void on_btnCancel_clicked();

  void onUserActionChanged();
private:
  Ui::CheckConstraintEditForm *ui;

  // AbstractDatabaseEditForm interface
public:
  virtual void objectToForm() override;
  virtual void formToObject() override;
};

#endif // CHECKCONSTRAINTEDITFORM_H
