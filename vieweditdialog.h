#ifndef VIEWEDITDIALOG_H
#define VIEWEDITDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>
#include <QDebug>
#include <QModelIndex>

namespace Ui {
class ViewEditDialog;
}

class ViewEditDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ViewEditDialog(QWidget *parent = 0);
  ~ViewEditDialog();

  void setModel(QAbstractItemModel* model);
private:
  Ui::ViewEditDialog *ui;
  QDataWidgetMapper *_mapper;
public slots:
  void onModelIndexChanged(QModelIndex index);
private slots:
  void on_btnOk_clicked();
  void on_btnCancel_clicked();
};

#endif // VIEWEDITDIALOG_H
