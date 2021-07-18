#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
  Q_OBJECT

public:
  explicit SettingsForm(QWidget *parent = nullptr);
  ~SettingsForm();

  static SettingsForm* instance();
private slots:
  void on_btnClose_clicked();

private:
  Ui::SettingsForm *ui;
  static SettingsForm* _singleton;
};

#endif // SETTINGSFORM_H
