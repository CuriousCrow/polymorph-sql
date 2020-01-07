#ifndef CONNECTIONEDITDIALOG_H
#define CONNECTIONEDITDIALOG_H

#include <QDialog>
#include "qstructureitemmodel.h"
#include "ldatawidgetmapper.h"

namespace Ui {
class ConnectionEditDialog;
}

class ConnectionEditDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ConnectionEditDialog(QWidget *parent = nullptr);
  ~ConnectionEditDialog();
  void setModel(QStructureItemModel* model);
  LDataWidgetMapper *mapper();
private slots:
  void on_btnOk_clicked();

  void on_btnBrowseLocalAddress_clicked();

  void on_btnTryToConnect_clicked();
  void on_btnCancel_clicked();

public slots:
  void onDatabaseIndexChanged(QModelIndex idx);
private:
  Ui::ConnectionEditDialog *ui;
  QStructureItemModel* _model;
  LDataWidgetMapper* _mapper;
  void removeUnavailableDriversFromCombobox();
};

#endif // CONNECTIONEDITDIALOG_H
