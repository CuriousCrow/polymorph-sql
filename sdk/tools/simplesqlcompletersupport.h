#ifndef SIMPLESQLCOMPLETERSUPPORT_H
#define SIMPLESQLCOMPLETERSUPPORT_H

#include <QObject>
#include "core/lknowledgebase.h"
#include "core/datastore.h"
#include "models/jointdbojbectmodel.h"
#include "tools/ltextcompleter.h"

class SimpleSqlCompleterSupport : public QObject
{
  Q_OBJECT
public:
  Q_INVOKABLE SimpleSqlCompleterSupport(QObject *parent = nullptr);
  INJECT(DataStore*, ds);
  Q_INVOKABLE void inject_kb_into_kb(LKnowledgeBase* kb);
  void setWidget(QWidget* editor);
  void setDatabaseItem(DBDatabaseItem* dbItem);
  void setItem(DBObjectItem* objItem);
  LDBObjectTableModel* objectsModel();
private:
  LKnowledgeBase* _kb;
  JointDBOjbectModel* _knowledgeModel;
  LDBObjectTableModel* _objectsModel;
  LTextCompleter* _completer;
  DBDatabaseItem* _dbItem;
  QString aliasSource(const QString &alias) const;
private slots:
  void onCompleterRequested(const QString &contextText);

};

#endif // SIMPLESQLCOMPLETERSUPPORT_H
