#ifndef BLOBEDITOR_H
#define BLOBEDITOR_H

#include <QDialog>

namespace Ui {
class BlobEditor;
}

class BlobEditor : public QDialog
{
  Q_OBJECT

public:
  explicit BlobEditor(QWidget *parent = nullptr);
  ~BlobEditor();

  void setData(QByteArray data);
  QByteArray data();
private slots:
  void on_btnClose_clicked();

  void on_btnApply_clicked();


private:
  Ui::BlobEditor *ui;
  QByteArray _data;
};

#endif // BLOBEDITOR_H
