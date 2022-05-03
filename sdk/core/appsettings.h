#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QSettings>

#define PRM_DATABASE "database"

class AppSettings
{
public:
    Q_INVOKABLE AppSettings();
    static QVariant val(QString name, QVariant defValue = QVariant());
    static QString strVal(QString name, QVariant defValue = QVariant());
    static int intVal(QString name, QVariant defValue = QVariant());
    static bool boolVal(QString name, QVariant defValue = QVariant());
    static void sync();
private:
    static QSettings* _settings;
};

#endif // APPSETTINGS_H
