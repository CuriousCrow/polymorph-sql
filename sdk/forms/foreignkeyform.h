#ifndef FOREIGNKEYFORM_H
#define FOREIGNKEYFORM_H

#include <QDialog>
#include "abstractdatabaseitemform.h"

namespace Ui {
  class ForeignKeyForm;
}

class ForeignKeyForm : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  explicit ForeignKeyForm(QWidget *parent = nullptr);
  ~ForeignKeyForm() override;

private:
  Ui::ForeignKeyForm *ui;

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

#endif // FOREIGNKEYFORM_H
