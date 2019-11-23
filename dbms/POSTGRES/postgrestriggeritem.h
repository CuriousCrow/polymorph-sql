#ifndef POSTGRESTRIGGERITEM_H
#define POSTGRESTRIGGERITEM_H

#include <QObject>
#include "../qdbtriggeritem.h"

class PostgresTriggerItem : public QDBTriggerItem
{
  Q_OBJECT
public:
  PostgresTriggerItem(QString caption, QObject* parent = nullptr);

  // QDBObjectItem interface
public:
  virtual bool refresh() override;
  virtual ActionResult insertMe() override;
  virtual ActionResult updateMe() override;
  virtual ActionResult deleteMe() override;
private:
  void setEventByName(QString event);
  void clearEventFields();
  QString parseActionStatement(QString statement);
  QStringList events();

};

#endif // POSTGRESTRIGGERITEM_H
