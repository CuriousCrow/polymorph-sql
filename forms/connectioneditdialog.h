#ifndef CONNECTIONEDITDIALOG_H
#define CONNECTIONEDITDIALOG_H

#include <QDialog>
#include "qstructureitemmodel.h"
#include "ldatawidgetmapper.h"
#include "abstractdatabaseitemform.h"

namespace Ui {
class ConnectionEditDialog;
}

class ConnectionEditDialog : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  explicit ConnectionEditDialog(QWidget *parent = nullptr);
  virtual ~ConnectionEditDialog() override;
private slots:
  void on_btnOk_clicked();

  void on_btnBrowseLocalAddress_clicked();

  void on_btnTryToConnect_clicked();
  void on_btnCancel_clicked();
  void on_btnCreate_clicked();

private:
  Ui::ConnectionEditDialog *ui;
  void removeUnavailableDriversFromCombobox();

  // AbstractDatabaseEditForm interface
public:
  virtual void objectToForm() override;
  virtual void formToObject() override;
};

#endif // CONNECTIONEDITDIALOG_H
