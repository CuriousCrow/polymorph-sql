#ifndef TRIGGEREDITFORM_H
#define TRIGGEREDITFORM_H

#include <QDialog>
#include "abstractdatabaseitemform.h"
#include "../objects/appconst.h"

namespace Ui {
class TriggerEditForm;
}

class TriggerEditForm : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  explicit TriggerEditForm(QWidget *parent = nullptr);
  ~TriggerEditForm();

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
