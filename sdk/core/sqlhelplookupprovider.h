#ifndef SQLHELPLOOKUPPROVIDER_H
#define SQLHELPLOOKUPPROVIDER_H

#include "qknowledgebase.h"
#include "../utils/qsimpletooltip.h"
#include "../models/lsqltablemodel.h"
#include "core/dependencycontainer.h"

class SqlHelpLookupProvider : public QObject, public HelpLookupProvider
{
    Q_OBJECT
public:
    Q_INVOKABLE SqlHelpLookupProvider(QObject* parent = nullptr);
    virtual QString lookup(QString keyword);

    Q_INVOKABLE void inject_by_kb(QKnowledgeBase* kb);
private:
    QList<LSqlTableModel*> _helpModels;
};

#endif // SQLHELPLOOKUPPROVIDER_H
