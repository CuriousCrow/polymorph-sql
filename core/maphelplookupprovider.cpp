#include "maphelplookupprovider.h"


MapHelpLookupProvider::MapHelpLookupProvider(QObject *parent) : QObject(parent)
{
}

QString MapHelpLookupProvider::lookup(QString keyword)
{
    return _dictMap.value(keyword, "No documentation found for " + keyword);
}

void MapHelpLookupProvider::addItem(QString keyword, QString text)
{
    _dictMap.insert(keyword, text);
}
