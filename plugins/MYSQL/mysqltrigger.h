#ifndef MYSQLTRIGGER_H
#define MYSQLTRIGGER_H

#include "objects/dbtriggeritem.h"
#include <QObject>

class MysqlTrigger : public DBTriggerItem
{
  Q_OBJECT
public:
  Q_INVOKABLE MysqlTrigger();

  // DBObjectItem interface
public:
  virtual bool refresh() override;
  virtual QString toDDL() const override;
  virtual ActionResult insertMe() override;
  virtual ActionResult updateMe() override;
  virtual ActionResult deleteMe() override;
private:
  void setEventByName(QString event);
  void clearEventFields();
  QString parseActionStatement(QString statement);
  QStringList events() const;
};

#endif // MYSQLTRIGGER_H
