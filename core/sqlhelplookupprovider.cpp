#include "sqlhelplookupprovider.h"


SqlHelpLookupProvider::SqlHelpLookupProvider(QObject *parent) : QObject(parent)
{
    _model = QKnowledgeBase::kb()->mKeywords;
}

QString SqlHelpLookupProvider::lookup(QString keyword)
{
    int row = _model->rowByValue("NAME", keyword.toLower());
    if (row < 0)
        return "Нет данных";
    else
        return _model->data(row, "DESCRIPTION").toString();
}
