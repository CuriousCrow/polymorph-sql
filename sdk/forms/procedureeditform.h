#ifndef PROCEDUREEDITFORM_H
#define PROCEDUREEDITFORM_H

#include <QDialog>
#include "abstractdatabaseitemform.h"
#include "core/dependencycontainer.h"
#include "tools/simplesqlcompletersupport.h"
#include "tools/lsqlsyntaxhighlighter.h"
#include "utils/lsimpletooltip.h"
#include "core/sqlhelplookupprovider.h"
#include "tools/sqleditorsupport.h"

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
//  Q_INVOKABLE void inject_sqlCompleterSupport_into_form(SimpleSqlCompleterSupport* completerSupport);
//  Q_INVOKABLE void inject_helpLookupProvider(SqlHelpLookupProvider* lookupProvider);
//  Q_INVOKABLE void inject_by_sqlSyntaxHighlighter(LSqlSyntaxHighlighter* syntaxHighlighter);
  INJECT(SqlEditorSupport*, editorSupport);

private:
  Ui::ProcedureEditForm *ui;
//  SimpleSqlCompleterSupport* _completerSupport;
//  LSqlSyntaxHighlighter* _highlighter;
//  LSimpleTooltip* _helpTooltip;
//  SqlHelpLookupProvider* _helpLookupProvider;

  void reloadTypes();

  // AbstractDatabaseEditForm interface
public:
  void objectToForm();
  void formToObject();
private slots:
  void on_btnApply_clicked();
  void on_btnCancel_clicked();
  void onUserActionChanged();
//  void onHelpKey();
};

#endif // PROCEDUREEDITFORM_H
