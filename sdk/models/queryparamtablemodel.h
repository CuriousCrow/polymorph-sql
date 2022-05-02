#ifndef QUERYPARAMTABLEMODEL_H
#define QUERYPARAMTABLEMODEL_H

#include <QAbstractTableModel>
#include <QObject>

class QueryParamTableModel : public QAbstractTableModel
{
  Q_OBJECT
public:
    QueryParamTableModel(QObject* parent = nullptr);
    void setParams(QVariantMap params);
    QVariantMap params() const;
    void updateParams(QVariantMap params);
    void deleteParam(QString name);
    void deleteParam(int row);
    void addParam(QString name, QVariant value = QVariant());
public slots:
    void clear();

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    virtual int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
private:
    QVariantMap _params;
    QString nameByRow(int row) const;
    int rowByName(const QString &name) const;


};

#endif // QUERYPARAMTABLEMODEL_H
