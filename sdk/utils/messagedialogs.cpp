#include "messagedialogs.h"
#include <QMessageBox>


void MessageDialogs::info(QString message, QString title)
{
  QMessageBox::warning(nullptr, title, message);
}

void MessageDialogs::warn(QString message, QString title)
{
  QMessageBox::warning(nullptr, title, message);
}

void MessageDialogs::error(QString message, QString title)
{
  QMessageBox::warning(nullptr, title, message);
}
