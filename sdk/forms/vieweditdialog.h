#ifndef VIEWEDITDIALOG_H
#define VIEWEDITDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>
#include <QModelIndex>
#include "abstractdatabaseitemform.h"

namespace Ui {
class ViewEditDialog;
}

class ViewEditDialog : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  Q_INVOKABLE ViewEditDialog();
  ~ViewEditDialog();

private:
  Ui::ViewEditDialog *ui;
private slots:
  void on_btnOk_clicked();
  void on_btnCancel_clicked();
  void onUserActionChanged();

  // AbstractDatabaseEditForm interface
public:
  void objectToForm() override;
  void formToObject() override;

  // NotifiableDialog interface
protected:
  virtual void localEvent(LocalEvent *event) override;
};

#endif // VIEWEDITDIALOG_H
