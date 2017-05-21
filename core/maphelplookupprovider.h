#ifndef MAPHELPLOOKUPPROVIDER_H
#define MAPHELPLOOKUPPROVIDER_H

#include <QMap>
#include "../utils/qsimpletooltip.h"

class MapHelpLookupProvider : public QObject, public HelpLookupProvider
{
    Q_OBJECT
public:
    MapHelpLookupProvider(QObject* parent = 0);
    virtual QString lookup(QString keyword);
    void addItem(QString keyword, QString text);
private:
    QMap<QString, QString> _dictMap;
};

#endif // MAPHELPLOOKUPPROVIDER_H
