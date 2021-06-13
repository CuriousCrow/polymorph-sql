#ifndef QUERYPARAMSFORM_H
#define QUERYPARAMSFORM_H

#include <QWidget>
#include <QMenu>
#include "../models/queryparamtablemodel.h"

namespace Ui {
class QueryParamsForm;
}

class QueryParamsForm : public QWidget
{
    Q_OBJECT

public:
    explicit QueryParamsForm(QWidget *parent = nullptr);
    ~QueryParamsForm();

    void setParams(QVariantMap params);
    QString applyParams(QString &sql);

private slots:
    void on_aRemoveParam_triggered();

    void on_tvParams_pressed(const QModelIndex &index);

    void on_btnAdd_clicked();

    void on_btnRemove_clicked();

private:
    Ui::QueryParamsForm *ui;
    QueryParamTableModel* _paramsModel;
    QMenu* _pmParams;
};

#endif // QUERYPARAMSFORM_H
