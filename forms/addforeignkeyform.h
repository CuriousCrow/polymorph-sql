#ifndef ADDFOREIGNKEYFORM_H
#define ADDFOREIGNKEYFORM_H

#include <QDialog>
#include "abstractdatabaseitemform.h"

namespace Ui {
class AddForeignKeyForm;
}

class AddForeignKeyForm : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  explicit AddForeignKeyForm(QWidget *parent = nullptr);
  ~AddForeignKeyForm() override;

private:
  Ui::AddForeignKeyForm *ui;

  // AbstractDatabaseEditForm interface
public:
  virtual void objectToForm() override;
  virtual void formToObject() override;
private slots:
  void on_btnApply_clicked();
  void on_btnCancel_clicked();
  void on_cmbReferenceTable_currentTextChanged(const QString &refTable);
  void onUserActionChanged();
};

#endif // ADDFOREIGNKEYFORM_H
