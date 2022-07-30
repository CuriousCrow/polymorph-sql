#ifndef SQLHELPLOOKUPPROVIDER_H
#define SQLHELPLOOKUPPROVIDER_H

#include "lknowledgebase.h"
#include "utils/lsimpletooltip.h"
#include "models/lsqltablemodel.h"
#include "core/dependencycontainer.h"

class SqlHelpLookupProvider : public QObject, public HelpLookupProvider
{
  Q_OBJECT
public:
  Q_INVOKABLE SqlHelpLookupProvider(QObject* parent = nullptr);
  virtual QString lookup(QString keyword);

  Q_INVOKABLE void inject_by_kb(LKnowledgeBase* kb);
  void updateHelpModels(QString driverName);
private:
  LKnowledgeBase* _kb;
  QList<LDBObjectTableModel*> _helpModels;
};

#endif // SQLHELPLOOKUPPROVIDER_H
