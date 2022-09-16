#ifndef FIREBIRDTRIGGER_H
#define FIREBIRDTRIGGER_H

#include "objects/dbtrigger.h"
#include "models/variantmaptablemodel.h"
#include <QObject>

class FirebirdTrigger : public DBTriggerItem
{
  Q_OBJECT
public:
  Q_INVOKABLE FirebirdTrigger();
  ~FirebirdTrigger();

  // DBObjectItem interface
public:
  virtual bool refresh() override;
  virtual QString toDDL() const override;
  virtual ActionResult insertMe() override;
  virtual ActionResult updateMe() override;
  virtual ActionResult deleteMe() override;
protected:
  void setEventByCode(int eventType);
  void clearEventFields();
  QString parseActionStatement(QString statement);
  QStringList events() const;
public:
  VariantMapTableModel* argumentInModel();
  VariantMapTableModel* argumentOutModel();
private:
  void refreshArguments();
  QString argsFromModel(VariantMapTableModel* argModel) const;
  VariantMapTableModel* _mInArguments;
  VariantMapTableModel* _mOutArguments;
};

#endif // FIREBIRDTRIGGER_H
