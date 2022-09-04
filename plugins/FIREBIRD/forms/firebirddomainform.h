#ifndef FIREBIRDDOMAINFORM_H
#define FIREBIRDDOMAINFORM_H

#include <QDialog>
#include "forms/abstractdatabaseitemform.h"
#include "firebirdtypeprovider.h"

namespace Ui {
class FirebirdDomainForm;
}

class FirebirdDomainForm : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  Q_INVOKABLE FirebirdDomainForm();
  ~FirebirdDomainForm();

  INJECT_AS(FirebirdTypeProvider*, typeProvider, firebirdTypeProvider)

private:
  Ui::FirebirdDomainForm *ui;

  // AbstractDatabaseEditForm interface
public:
  virtual void objectToForm() override;
  virtual void formToObject() override;
private slots:
  void on_btnCancel_clicked();
  void on_btnApply_clicked();
  void on_cmbType_currentTextChanged(const QString &type);
};

#endif // FIREBIRDDOMAINFORM_H
