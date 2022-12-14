#ifndef MAPHELPLOOKUPPROVIDER_H
#define MAPHELPLOOKUPPROVIDER_H

#include <QMap>
#include "utils/lsimpletooltip.h"

class MapHelpLookupProvider : public QObject, public HelpLookupProvider
{
    Q_OBJECT
public:
    MapHelpLookupProvider(QObject* parent = nullptr);
    virtual QString lookup(QString keyword);
    void addItem(QString keyword, QString text);
private:
    QMap<QString, QString> _dictMap;
};

#endif // MAPHELPLOOKUPPROVIDER_H
