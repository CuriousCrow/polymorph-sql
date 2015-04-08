#ifndef CONNECTIONEDITDIALOG_H
#define CONNECTIONEDITDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class ConnectionEditDialog;
}

class ConnectionEditDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ConnectionEditDialog(QWidget *parent = 0);
  ~ConnectionEditDialog();
  void setModel(QSqlTableModel* sqlmodel);
private slots:
  void on_cbServerType_activated(int index);
  void on_btnOk_clicked();

  void on_btnBrowseLocalAddress_clicked();

public slots:
  void onDatabaseIndexChanged(QModelIndex idx);
private:
  Ui::ConnectionEditDialog *ui;
  QSqlTableModel* model;
  QDataWidgetMapper* mapper;
};

#endif // CONNECTIONEDITDIALOG_H
