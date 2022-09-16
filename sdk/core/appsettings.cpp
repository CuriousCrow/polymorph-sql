#include "appsettings.h"
#include <QApplication>
#include <QDebug>

QSettings* AppSettings::_settings = nullptr;

AppSettings::AppSettings() {
}

QVariant AppSettings::val(QString name, QVariant defValue)
{
  if (!_settings) {
    QString settingsPath = QApplication::applicationDirPath() + "/polymorphmanager.ini";
    qDebug() << "Loading settings: " + settingsPath;
    _settings = new QSettings(settingsPath, QSettings::IniFormat);
  }
  return _settings->value(name, defValue);
}

QString AppSettings::strVal(QString name, QVariant defValue)
{
  return val(name, defValue).toString();
}

int AppSettings::intVal(QString name, QVariant defValue)
{
  return val(name, defValue).toInt();
}

bool AppSettings::boolVal(QString name, QVariant defValue)
{
  return val(name, defValue).toBool();
}

void AppSettings::sync()
{
  val("");
  _settings->sync();
}
