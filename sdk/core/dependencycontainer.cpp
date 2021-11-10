#include "dependencycontainer.h"
#include <QDebug>
#include <QMetaMethod>


DependencyContainer::DependencyContainer(QObject *parent) : QObject(parent)
{
    qDebug() << "Dependency container constructor";
}

DependencyContainer::~DependencyContainer()
{
    qDebug() << "Dependency container destructor";

    while(!_singletonHash.isEmpty()) {
        QStringList keys = _singletonHash.keys();
        QString name = keys.first();
        QObject* obj = _singletonHash.value(name);
        _singletonHash.remove(name);
        delete obj;
    }
}

DependencyMeta *DependencyContainer::registerDependency(DependencyMeta *meta)
{
    QString checkResult = dependencyCheck(meta);
    if (!checkResult.isEmpty()) {
      qDebug() << "Dependency check failed:" << meta << checkResult;
      return meta;
    }
    qDebug() << QString("Registering dependency: %1").arg(meta->toString());
    QStringList classes = meta->ancessors();
    foreach(QString className, classes) {
        _metaByClass.insert(className, meta);
    }
    _metaByName.insert(meta->name(), meta);
    return meta;
}

DependencyMeta *DependencyContainer::registerDependency(QString name, const QMetaObject *metaObj, InstanceMode mode)
{
    return registerDependency(new DependencyMeta(name, metaObj, mode));
}

DependencyMeta *DependencyContainer::registerSingletonObject(DependencyMeta *meta, QObject *object)
{
    if (meta->mode() != InstanceMode::Singleton) {
        qWarning() << "RegisterSingletonObject method only with singleton mode";
        return nullptr;
    }
    _singletonHash.insert(meta->name(), object);
    return registerDependency(meta);
}

void DependencyContainer::removeSingleton(QString name)
{
    _singletonHash.remove(name);
}

QStringList DependencyContainer::namesByClass(QString className)
{
    QStringList resList;
    foreach(DependencyMeta* meta, _metaByClass.values(className)) {
        resList.append(meta->name());
    }
    return resList;
}

QObject *DependencyContainer::dependency(const QString &className, const QVariantHash &params)
{
    qDebug() << "Dependency request of class:" << className;
    if (!_metaByClass.contains(className)) {
        qWarning() << "No dependency registered implementing:" << className;
        return nullptr;
    }
    QList<DependencyMeta*> metaList = _metaByClass.values(className);
    foreach(DependencyMeta* meta, metaList) {
        if (meta->exactClassMatch(className))
            return dependency(meta->name());
        if (meta->hasMatch(params))
            return dependency(meta->name());
    }
    qWarning() << "Meta object not registered:" << className << params;
    return nullptr;
}

QObject *DependencyContainer::dependency(const QString &name)
{
    qDebug() << "Dependency request:" << name;
    if (!_metaByName.contains(name)) {
        qCritical() << QString("Dependency %1 not registered in the dependency container").arg(name);
        return nullptr;
    }
    DependencyMeta* meta = _metaByName.value(name);
    const QMetaObject* metaObj = meta->metaObj();

    //Если одиночка, то поискать в уже созданных
    if (meta->mode() == InstanceMode::Singleton) {
        if (_singletonHash.contains(name)) {
            qDebug() << QString("Singleton object found: %1").arg(name);
            return _singletonHash.value(name);
        }
    }
    if (metaObj->constructorCount() == 0) {
        qCritical() << QString("No constructor for type %1 is available. Please, mark at least one constructor with Q_INVOKABLE macro").arg(metaObj->className());
        return nullptr;
    }

    //Check for default constructor
    bool hasDefaultConstructor = false;
    for(int i=0; i<metaObj->constructorCount(); i++) {
        if (metaObj->constructor(i).parameterCount() == 0) {
            hasDefaultConstructor = true;
            break;
        }
    }
    if (!hasDefaultConstructor) {
        qWarning() << QString("No default constructor for class %1 or it has not been marked with Q_INVOKABLE macro")
                      .arg(metaObj->className());
        return nullptr;
    }

    QObject* newObj = metaObj->newInstance();
    if (!newObj) {
        qWarning() << "Cant instantiate object:" << name;
        return nullptr;
    }
    qDebug() << "Bean created of metaobject:" << name;
    for(int i=0; i<metaObj->methodCount(); i++) {
        QMetaMethod method = metaObj->method(i);
        QString methodName = method.name();
        if (methodName.contains(INJECT_PREFIX)) {
            qDebug() << "Inject method detected:" << methodName;
            QString injectCommand = methodName;
            QStringList injectTokens = injectCommand.split("_", Qt::SkipEmptyParts);
            //Not injectMethod
            if (injectTokens.size() < 2)
                continue;
            QString beanName;
            if (injectTokens.contains("by"))
                beanName = injectTokens[injectTokens.indexOf("by") + 1];
            else
                beanName = injectTokens[1];
            QObject* dependencyObj = dependency(beanName);
            if (!dependencyObj)
                continue;
            QString argType = QString::fromLatin1(method.parameterTypes().at(0)).remove("*").trimmed();

            if (!dependencyObj->inherits(argType.toLatin1())) {
                QString errStr = "Bean %1: Inject method %2 expects arg type %3 descedant. Found bean (%4) instead";
                qCritical() << errStr.arg(name, methodName, argType, beanName, dependencyObj->metaObject()->className());
                continue;
            }

            bool injectResult = method.invoke(newObj, Qt::DirectConnection, QGenericArgument(method.parameterTypes().at(0), &dependencyObj));

            qDebug() << QString("Inject method %1 result: %2").arg(methodName).arg(injectResult);
        }
    }
    newInstanceProccessing(newObj);
    //Добавить одиночку
    if (meta->mode() == InstanceMode::Singleton) {
        _singletonHash.insert(name, newObj);
    }
    qDebug() << "Dependency" << name << "successfully instatiated" << "\n";
    return newObj;
}

QString DependencyContainer::dependencyCheck(const DependencyMeta *meta)
{
  Q_UNUSED(meta)
  //By default no dependency check
  return "";
}

bool DependencyContainer::dependencyFilter(const DependencyMeta *meta)
{
  Q_UNUSED(meta)
  //By default no filter
  return true;
}

void DependencyContainer::newInstanceProccessing(QObject *obj)
{
  Q_UNUSED(obj)
  //By default do nothing
}


DependencyMeta::DependencyMeta(QString name, const QMetaObject* metaObj, InstanceMode mode) : QVariantHash(),
    _name(name), _instanceMode(mode), _metaObj(metaObj)
{

}

QString DependencyMeta::name() const
{
    return _name;
}

InstanceMode DependencyMeta::mode() const
{
    return _instanceMode;
}

QStringList DependencyMeta::ancessors() const
{
//    qDebug() << "Bean" << name() << "implements:";
    QStringList list;
    addSuperClass(_metaObj, list);
//    qDebug() << "end";
    return list;
}

const QMetaObject* DependencyMeta::metaObj() const
{
    return _metaObj;
}

DependencyMeta *DependencyMeta::setParam(QString name, QVariant value)
{
    insert(name, value);
    return this;
}


bool DependencyMeta::hasMatch(QVariantHash params) const
{
    QStringList keys = params.keys();
    for(int i=0; i<keys.count(); i++) {
        QString key = keys.value(i);
        if (value(key) != params.value(key))
            return false;
    }
    return true;
}

bool DependencyMeta::exactClassMatch(const QString &className) const
{
    return contains(PRM_CLASS) && value(PRM_CLASS).toString() == className;
}

QString DependencyMeta::toString() const
{
    QString pattern = "%1=%2";
    QStringList params;
    params.append(pattern.arg("name", name()));
    params.append(pattern.arg("class", metaObj()->className()));
    params.append(pattern.arg("instanceMode", _instanceMode == InstanceMode::Singleton ? "Singleton" : "Prototype"));
    return params.join(", ");
}

void DependencyMeta::addSuperClass(const QMetaObject *metaObj, QStringList &list) const
{
    list.append(metaObj->className());
//    qDebug() << metaObj->className();
    if (metaObj->superClass()) {
        addSuperClass(metaObj->superClass(), list);
    }
}
