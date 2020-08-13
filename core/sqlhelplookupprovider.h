#ifndef SQLHELPLOOKUPPROVIDER_H
#define SQLHELPLOOKUPPROVIDER_H

#include "../qknowledgebase.h"
#include "../utils/qsimpletooltip.h"
#include "../qknowledgebase.h"
#include "../models/lsqltablemodel.h"

class SqlHelpLookupProvider : public QObject, public HelpLookupProvider
{
public:
    SqlHelpLookupProvider(QObject* parent = nullptr);
    virtual QString lookup(QString keyword);
private:
    LSqlTableModel* _model;
};

#endif // SQLHELPLOOKUPPROVIDER_H
