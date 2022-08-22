#ifndef MYSQLPROCEDUREEDITFORM_H
#define MYSQLPROCEDUREEDITFORM_H

#include <QDialog>
#include "forms/abstractdatabaseitemform.h"
#include "models/variantmaptablemodel.h"
#include "tools/sqleditorsupport.h"

namespace Ui {
class MysqlProcedureEditForm;
}


class MysqlProcedureEditForm : public AbstractDatabaseEditForm
{
  Q_OBJECT

public:
  Q_INVOKABLE MysqlProcedureEditForm();
  ~MysqlProcedureEditForm();

  INJECT(SqlEditorSupport*, editorSupport);

private slots:
  void on_btnApply_clicked();
  void on_btnClose_clicked();

  void on_edtName_textChanged(const QString &name);

  void on_btnAddArg_clicked();
  void on_btnDeleteArg_clicked();

private:
  Ui::MysqlProcedureEditForm *ui;
  VariantMapTableModel* _argModel;
  int _maxId = 0;

  // AbstractDatabaseEditForm interface
public:
  virtual void objectToForm() override;
  virtual void formToObject() override;
};

#endif // MYSQLPROCEDUREEDITFORM_H
