#ifndef VIEWEDITDIALOG_H
#define VIEWEDITDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>
#include <QModelIndex>
#include "abstractdatabaseitemform.h"
#include "tools/simplesqlcompletersupport.h"

namespace Ui {
class ViewEditDialog;
}

class ViewEditDialog : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  Q_INVOKABLE ViewEditDialog();
  ~ViewEditDialog();

  Q_INVOKABLE void inject_sqlCompleterSupport_into_form(SimpleSqlCompleterSupport* completerSupport);

private:
  Ui::ViewEditDialog *ui;
  SimpleSqlCompleterSupport* _completerSupport;

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
