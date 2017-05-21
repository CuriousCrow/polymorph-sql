#ifndef LCACHEDTABLEMODEL_H
#define LCACHEDTABLEMODEL_H

#include <QMap>
#include <QAbstractTableModel>

class LVariantRec
{
public:
    LVariantRec();
    LVariantRec(const LVariantRec &obj);
    QVariant value(QString field) const;
    void setValue(QString field, QVariant val);
private:
    QMap<QString, QVariant> _dataMap;
};


class LCachedTableModel : public QAbstractTableModel
{
public:
    LCachedTableModel(QObject *parent = Q_NULLPTR);
    void registerField(QString field);
    void addRec(LVariantRec rec);
    void setIdField(QString field);

private:
    LVariantRec _sampleRec = LVariantRec();
    qlonglong _defIdGen = 1;
    int _idColIdx;
    QList<QString> _fieldNames;
    QList<QVariant> _idList;
    QMap<QVariant, LVariantRec> _rows;
    QMap<QVariant, LVariantRec> _changes;
    QVariant idByRow(int row) const;
    QString fieldByIndex(int col) const;
    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    // QAbstractItemModel interface
public slots:
    virtual void revert();
    bool submitAll();
    virtual bool insertRows(int row, int count, const QModelIndex &parent);
    virtual bool removeRows(int row, int count, const QModelIndex &parent);
};

#endif // LCACHEDTABLEMODEL_H
