#ifndef TABLEEDITFORM_H
#define TABLEEDITFORM_H

#include <QDialog>
#include "abstractdatabaseitemform.h"
#include "../tablerowmodel.h"
#include "qdbtableitem.h"
#include "comboboxhashdelegate.h"

namespace Ui {
class TableEditForm;
}

class TableEditForm : public AbstractDatabaseEditForm
{
    Q_OBJECT

public:
    explicit TableEditForm(QWidget *parent = 0);
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
private:
    ComboboxHashDelegate* _colTypeDelegate;
};

#endif // TABLEEDITFORM_H
