#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QList>
#include "../core/iocplugin.h"
#include "../objects/appconst.h"

class Core : public DependencyContainer
{
  Q_OBJECT
public:
  static Core* instance(QObject* parent = nullptr);
  static void registerPlugin(IocPlugin* plugin);
  static IocPlugin* plugin(QString driver, FeatureType featureType);
  QStringList pluginNames() const;
  QStringList supportedDrivers() const;
  QList<IocPlugin*> plugins();

  AbstractDatabaseEditForm* objectForm(const QString &driver, DBObjectItem::ItemType itemType);

  template<class T>
  T* dependencyForDriver(const QString &driver){
      static_assert (std::is_base_of<QObject,T>::value, ERR_ONLY_QOBJECT);
      QVariantHash p;
      p.insert(F_DRIVER_NAME, driver);
      T* obj = dependency<T>(p);
      if (obj)
          return obj;
      p.insert(F_DRIVER_NAME, "");
      return dependency<T>(p);
  }
signals:

public slots:

private:
  explicit Core(QObject *parent = nullptr);
  QList<IocPlugin*> _plugins;
  QHash<QString, IocPlugin*> _modules;
//  DependencyContainer* _container;
  static Core* _singleton;
};

#endif // CORE_H
