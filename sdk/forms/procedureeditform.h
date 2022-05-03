#ifndef PROCEDUREEDITFORM_H
#define PROCEDUREEDITFORM_H

#include <QDialog>
#include "abstractdatabaseitemform.h"
#include "core/dependencycontainer.h"
#include "tools/simplesqlcompletersupport.h"

namespace Ui {
class ProcedureEditForm;
}

class ProcedureEditForm : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  Q_INVOKABLE ProcedureEditForm();
  ~ProcedureEditForm();

  INJECT(LKnowledgeBase*, kb);
  Q_INVOKABLE void inject_sqlCompleterSupport_into_form(SimpleSqlCompleterSupport* completerSupport);

private:
  Ui::ProcedureEditForm *ui;
  SimpleSqlCompleterSupport* _completerSupport;

  void reloadTypes();

  // AbstractDatabaseEditForm interface
public:
  void objectToForm();
  void formToObject();
private slots:
  void on_btnApply_clicked();
  void on_btnCancel_clicked();
  void onUserActionChanged();
};

#endif // PROCEDUREEDITFORM_H
