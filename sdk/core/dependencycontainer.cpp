#include "dependencycontainer.h"
#include <QDebug>
#include <QMetaMethod>


DependencyContainer::DependencyContainer(QObject *parent) : QObject(parent)
{
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

void DependencyContainer::registerDependency(DependencyMeta* meta)
{
    QStringList classes = meta->ancessors();
    foreach(QString className, classes) {
        _metaByClass.insert(className, meta);
    }
    _metaByName.insert(meta->name(), meta);
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
        qCritical() << "Meta object" << name << "not registered in the dependency container";
        return nullptr;
    }
    DependencyMeta* meta = _metaByName.value(name);
    const QMetaObject* metaObj = meta->metaObj();

    //Если одиночка, то поискать в уже созданных
    if (meta->mode() == InstanceMode::Singleton) {
        if (_singletonHash.contains(name))
            return _singletonHash.value(name);
    }
    QObject* newObj = metaObj->newInstance();
    if (!newObj) {
        qWarning() << "Cant instantiate object:" << name;
        return nullptr;
    }
    qDebug() << "Bean created of metaobject:" << name;
    for(int i=0; i<metaObj->methodCount(); i++) {
        QString methodName = metaObj->method(i).name();
        if (methodName.contains(INJECT_PREFIX)) {
            qDebug() << "Method:" << methodName;
            QString dependencyName = methodName;
            dependencyName.remove(INJECT_PREFIX);
            QObject* dependencyObj = dependency(dependencyName);
            if (!dependencyObj)
                continue;
            qDebug() << "Inject bean:" << methodName;
            metaObj->invokeMethod(newObj, methodName.toLocal8Bit(), Qt::DirectConnection, Q_ARG(QObject*, dependencyObj));
        }

    }
    //Добавить одиночку
    if (meta->mode() == InstanceMode::Singleton) {
        _singletonHash.insert(name, newObj);
    }
    qDebug() << "Dependency" << name << "successfully instatiated";
    return newObj;
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
    qDebug() << "Bean" << name() << "implements:";
    QStringList list;
    addSuperClass(_metaObj, list);
    qDebug() << "end";
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

void DependencyMeta::addSuperClass(const QMetaObject *metaObj, QStringList &list) const
{
    list.append(metaObj->className());
    qDebug() << metaObj->className();
    if (metaObj->superClass()) {
        addSuperClass(metaObj->superClass(), list);
    }
}
