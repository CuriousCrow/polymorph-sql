#ifndef ABSTRACTPLUGIN_H
#define ABSTRACTPLUGIN_H

#include <QFlags>

enum FeatureType {
    DbmsObjects = 1,
    DbmsForms = 2,
    FormActions = 4
};

Q_DECLARE_FLAGS(FeatureTypes, FeatureType)
Q_DECLARE_OPERATORS_FOR_FLAGS(FeatureTypes)

class AbstractPlugin {
public:
    virtual QString title() = 0;
    virtual QString author() = 0;
    virtual int majorVersion() = 0;
    virtual int minorVersion() = 0;
    virtual FeatureTypes featureTypes() = 0;
    virtual bool driverSupported(QString driverName) = 0;
    virtual QString driver() = 0;
};


#endif // ABSTRACTPLUGIN_H
