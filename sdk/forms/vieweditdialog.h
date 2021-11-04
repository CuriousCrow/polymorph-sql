#ifndef VIEWEDITDIALOG_H
#define VIEWEDITDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>
#include <QModelIndex>
#include "core/datastore.h"
#include "models/jointdbojbectmodel.h"
#include "tools/ltextcompleter.h"
#include "tools/lsqlsyntaxhighlighter.h"
#include "abstractdatabaseitemform.h"

namespace Ui {
class ViewEditDialog;
}

class ViewEditDialog : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  Q_INVOKABLE ViewEditDialog();
  ~ViewEditDialog();

  INJECT(DataStore*, ds);
  Q_INVOKABLE void inject_kb_into_kb(LKnowledgeBase* kb);

private:
  Ui::ViewEditDialog *ui;
  LKnowledgeBase* _kb;
  JointDBOjbectModel* _knowledgeModel;
  LDBObjectTableModel* _objectsModel;
  LSqlSyntaxHighlighter* _highlighter;
  LTextCompleter* _completer;

private slots:
  void on_btnOk_clicked();
  void on_btnCancel_clicked();
  void onUserActionChanged();

  // AbstractDatabaseEditForm interface
public:
  void objectToForm() override;
  void formToObject() override;

  // NotifiableDialog interface
protected:
  virtual void localEvent(LocalEvent *event) override;
};

#endif // VIEWEDITDIALOG_H
