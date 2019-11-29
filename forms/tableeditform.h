#ifndef TABLEEDITFORM_H
#define TABLEEDITFORM_H

#include <QDialog>
#include <QMenu>
#include "abstractdatabaseitemform.h"
#include "../tablerowmodel.h"
#include "../dbms/qdbtableitem.h"
#include "comboboxhashdelegate.h"
#include "addforeignkeyform.h"

namespace Ui {
class TableEditForm;
}

class TableEditForm : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  explicit TableEditForm(QWidget *parent = nullptr);
  ~TableEditForm();

private:
  Ui::TableEditForm *ui;
  // AbstractDatabaseEditForm interface
public:
  virtual void objectToForm();
  virtual void formToObject();
private slots:
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
  void on_btnAdd_clicked();
  void on_btnDelete_clicked();
  void on_btnDropConstraint_clicked();

  void onShowForeignKeyEditor();
  void onShowUniqueConstraintEditor();
  void onShowCheckConstraintEditor();

  void onNewForeignKeySuccess();
  void onNewForeignKeyCanceled();
private:
  ComboboxHashDelegate* _colTypeDelegate;
  QMenu* _menuAddConstraint;

};

#endif // TABLEEDITFORM_H
