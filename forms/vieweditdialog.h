#ifndef VIEWEDITDIALOG_H
#define VIEWEDITDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>
#include <QDebug>
#include <QModelIndex>
#include "abstractdatabaseitemform.h"

namespace Ui {
class ViewEditDialog;
}

class ViewEditDialog : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  explicit ViewEditDialog(QWidget *parent = nullptr);
  ~ViewEditDialog();

private:
  Ui::ViewEditDialog *ui;
private slots:
  void on_btnOk_clicked();
  void on_btnCancel_clicked();
  void onUserActionChanged();

  // AbstractDatabaseEditForm interface
public:
  void objectToForm();
  void formToObject();
};

#endif // VIEWEDITDIALOG_H
