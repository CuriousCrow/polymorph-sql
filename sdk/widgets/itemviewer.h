#ifndef ITEMVIEWER_H
#define ITEMVIEWER_H

#include <QStackedWidget>
#include <QObject>
#include <QVariant>

namespace Ui {
class ItemViewer;
}

class ItemViewer : public QStackedWidget
{
  Q_OBJECT

  enum EditorType {
    Text = 0,
    Image = 1
  };

public:
  explicit ItemViewer(QWidget *parent = nullptr);
  ~ItemViewer();

  void setValue(QVariant value);
private:
  Ui::ItemViewer *ui;
  QVariant _itemValue;
  void setTypeByValue();
};

#endif // ITEMVIEWER_H
