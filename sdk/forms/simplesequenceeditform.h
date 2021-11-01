#ifndef SIMPLESEQUENCEEDITFORM_H
#define SIMPLESEQUENCEEDITFORM_H

#include <QDialog>
#include "forms/abstractdatabaseitemform.h"

namespace Ui {
class SimpleSequenceEditForm;
}

class SimpleSequenceEditForm : public AbstractDatabaseEditForm
{
    Q_OBJECT

public:
    Q_INVOKABLE SimpleSequenceEditForm(QWidget *parent = nullptr);
    virtual ~SimpleSequenceEditForm();

private slots:
    void on_btnCancel_clicked();

    void on_btnApply_clicked();

private:
    Ui::SimpleSequenceEditForm *ui;

    // AbstractDatabaseEditForm interface
public:
    virtual void objectToForm() override;
    virtual void formToObject() override;
};

#endif // SIMPLESEQUENCEEDITFORM_H
