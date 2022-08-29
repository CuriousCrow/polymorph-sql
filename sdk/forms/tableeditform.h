#ifndef TABLEEDITFORM_H
#define TABLEEDITFORM_H

#include <QDialog>
#include <QMenu>
#include "abstractdatabaseitemform.h"
#include "models/tablerowmodel.h"
#include "objects/dbtableitem.h"
#include "objects/typeprovider.h"
#include "models/comboboxitemdelegate.h"
#include "core/core.h"
#include "core/dependencycontainer.h"
#include "core/lknowledgebase.h"

namespace Ui {
class TableEditForm;
}

class TableEditForm : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  Q_INVOKABLE TableEditForm();
  ~TableEditForm();

  INJECT(Core*, core)
  INJECT(LKnowledgeBase*, kb)
private:
  Ui::TableEditForm *ui;
  // AbstractDatabaseEditForm interface
public:
  virtual void objectToForm();
  virtual void formToObject();
private slots:
  void on_btnApply_clicked();
  void on_btnClose_clicked();
  void on_btnAdd_clicked();
  void on_btnDelete_clicked();
  void on_btnDropConstraint_clicked();

  void onShowPrimaryKeyEditor();
  void onShowForeignKeyEditor();
  void onShowUniqueConstraintEditor();
  void onShowCheckConstraintEditor();

  void showCreateConstraintEditor(QString namePrefix, DBObjectItem::ItemType objType);
  void showViewConstraintEditor(const QModelIndex& index);
  void openConstraintEditor(DBObjectItem* obj, AbstractDatabaseEditForm::UserAction action);

  void onNewConstraintApply();
  void onNewConstraintCancel();
  void on_tvConstraints_doubleClicked(const QModelIndex &index);

private:
  DBObjectItem::ItemType typeByName(QString typeName);
  ComboboxItemDelegate* _colTypeDelegate;
  TypeProvider* _typeProvider;
  QMenu* _menuAddConstraint;

};

#endif // TABLEEDITFORM_H
