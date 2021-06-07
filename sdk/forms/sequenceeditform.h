#ifndef SEQUENCEEDITFORM_H
#define SEQUENCEEDITFORM_H

#include <QDialog>
#include "abstractdatabaseitemform.h"

namespace Ui {
class SequenceEditForm;
}

class SequenceEditForm : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  Q_INVOKABLE SequenceEditForm();
  ~SequenceEditForm();

private slots:
  void on_btnApply_clicked();

  void on_btnCancel_clicked();


private:
  Ui::SequenceEditForm *ui;

  // AbstractDatabaseEditForm interface
public:
  void objectToForm();
  void formToObject();
};

#endif // SEQUENCEEDITFORM_H
