#include "queryparamsform.h"
#include "ui_queryparamsform.h"

QueryParamsForm::QueryParamsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryParamsForm)
{
    ui->setupUi(this);

    _paramsModel = new QueryParamTableModel(this);
    connect(ui->btnClear, &QToolButton::clicked,
            _paramsModel, &QueryParamTableModel::clear);

    ui->tvParams->setModel(_paramsModel);

    _pmParams = new QMenu();
    _pmParams->addAction(ui->aRemoveParam);
}

QueryParamsForm::~QueryParamsForm()
{
    delete ui;
}

void QueryParamsForm::setParams(QVariantMap params)
{
    _paramsModel->updateParams(params);
}

QString QueryParamsForm::applyParams(QString &sql)
{
    QVariantMap map = _paramsModel->params();
    QString res = sql;
    QMapIterator<QString, QVariant> i(map);
    while(i.hasNext()) {
       i.next();
       res = res.replace("#" + i.key() + "#", i.value().toString());
    }
    return res;
}

void QueryParamsForm::on_aRemoveParam_triggered()
{
    int selected = ui->tvParams->currentIndex().row();
    if (selected < 0)
        return;
    _paramsModel->deleteParam(selected);
}

void QueryParamsForm::on_tvParams_pressed(const QModelIndex &index)
{
    Q_UNUSED(index)
    if (QApplication::mouseButtons().testFlag(Qt::RightButton)) {
      _pmParams->popup(QCursor::pos());
    }
}

void QueryParamsForm::on_btnAdd_clicked()
{
    _paramsModel->addParam("", "");
}

void QueryParamsForm::on_btnRemove_clicked()
{
    ui->aRemoveParam->trigger();
}
