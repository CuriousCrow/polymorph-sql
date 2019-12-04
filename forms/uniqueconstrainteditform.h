#ifndef UNIQUECONSTRAINTEDITFORM_H
#define UNIQUECONSTRAINTEDITFORM_H

#include <QDialog>
#include "abstractdatabaseitemform.h"

namespace Ui {
class UniqueConstraintEditForm;
}

class UniqueConstraintEditForm : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  explicit UniqueConstraintEditForm(QWidget *parent = nullptr);
  ~UniqueConstraintEditForm() override;

private:
  Ui::UniqueConstraintEditForm *ui;

  // AbstractDatabaseEditForm interface
public:
  virtual void objectToForm() override;
  virtual void formToObject() override;
private slots:
  void on_btnApply_clicked();
  void on_btnCancel_clicked();
};

#endif // UNIQUECONSTRAINTEDITFORM_H
