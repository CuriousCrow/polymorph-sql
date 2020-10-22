#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "../dbms/dbmsplugin.h"

class Core : public QObject
{
  Q_OBJECT
public:
  static Core* instance(QObject* parent = nullptr);
  static void registerModule(DbmsPlugin* module);
  static DbmsPlugin* module(QString name);
  QStringList moduleNames() const;
signals:

public slots:

private:
  explicit Core(QObject *parent = nullptr);
  QHash<QString, DbmsPlugin*> _modules;
  static Core* _singleton;
};

#endif // CORE_H
