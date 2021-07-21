#ifndef DEPENDENCYCONTAINER_H
#define DEPENDENCYCONTAINER_H

#include <QObject>
#include <QHash>
#include <QSet>
#include <QMap>
#include <QMultiHash>
#include <QVariantMap>


#define INJECT_PREFIX "inject_"
#define INJECT(Type, Name) Type _##Name; Q_INVOKABLE void inject_##Name(QObject* obj){ _##Name = static_cast<Type>(obj); }
#define INJECT_INITIALIZE(Type, Member, Name) Q_INVOKABLE void inject_##Member##_by_##Name(QObject* obj){ Member = static_cast<Type>(obj); }
#define CLASS(Type) Type::staticMetaObject.className()
#define CLASSMETA(Type) &Type::staticMetaObject

#define PRM_NAME "name"
#define PRM_CLASS "class"
#define PRM_MODE "mode"
#define PRM_CLASS_PREFIX "class_"

#define ERR_ONLY_QOBJECT "Only QObject descedants allowed"

enum InstanceMode {
    Singleton = 0,
    Prototype = 1
};

class DependencyMeta : public QVariantHash
{
public:
    DependencyMeta(QString name, const QMetaObject* metaObj, InstanceMode mode = Singleton);
    QString name() const;
    InstanceMode mode() const;
    QStringList ancessors() const;
    const QMetaObject* metaObj() const;

    DependencyMeta* setParam(QString name, QVariant value);

    bool hasMatch(QVariantHash params) const;
    bool exactClassMatch(const QString &className) const;

    QString toString() const;
private:
    QString _name;
    InstanceMode _instanceMode;
    const QMetaObject* _metaObj;
    void addSuperClass(const QMetaObject *metaObj, QStringList &list) const;
};

class DependencyContainer : public QObject
{
    Q_OBJECT
public:
    explicit DependencyContainer(QObject *parent = nullptr);
    virtual ~DependencyContainer();
    DependencyMeta* registerDependency(DependencyMeta* meta);
    DependencyMeta* registerSingletonObject(DependencyMeta* meta, QObject* object);
    void removeSingleton(QString name);

    QStringList namesByClass(QString className);

    QObject* dependency(const QString &className, const QVariantHash &params);
    QObject* dependency(const QString &name);

    template<class T>
    QStringList namesByClass(){
        static_assert (std::is_base_of<QObject,T>::value, ERR_ONLY_QOBJECT);
        return namesByClass(CLASS(T));
    }

    template<class T>
    T* dependency(const QVariantHash &params){
        static_assert (std::is_base_of<QObject,T>::value, ERR_ONLY_QOBJECT);
        return static_cast<T*>(dependency(CLASS(T), params));
    }
    template<class T>
    T* dependency(const QString &name){
        static_assert (std::is_base_of<QObject,T>::value, ERR_ONLY_QOBJECT);
        return static_cast<T*>(dependency(name));
    }
signals:

private:
    QHash<QString, DependencyMeta*> _metaByName; //itemByName
    QMultiHash<QString, DependencyMeta*> _metaByClass;

    QHash<QString, QObject*> _singletonHash; //all instaciated singletons
};

#define DependencyContainer_iid "ru.levolex.dependencycontainer"
Q_DECLARE_INTERFACE(DependencyContainer, DependencyContainer_iid)


#endif // DEPENDENCYCONTAINER_H
