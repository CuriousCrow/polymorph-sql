#ifndef POSTGRESTRIGGER_H
#define POSTGRESTRIGGER_H

#include <QObject>
#include "objects/dbtrigger.h"

/** PostgreSQL trigger item */
class PostgresTriggerItem : public DBTriggerItem
{
  Q_OBJECT
public:
  Q_INVOKABLE PostgresTriggerItem();

  // DBObjectItem interface
public:
  virtual bool refresh() Q_DECL_OVERRIDE;
  virtual ActionResult insertMe() Q_DECL_OVERRIDE;
  virtual ActionResult updateMe() Q_DECL_OVERRIDE;
  virtual ActionResult deleteMe() Q_DECL_OVERRIDE;
  virtual QString toDDL() const Q_DECL_OVERRIDE;
private:
  void setEventByName(QString event);
  void clearEventFields();
  QString parseActionStatement(QString statement);
  QStringList events() const;
};

#endif // POSTGRESTRIGGER_H
