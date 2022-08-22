#ifndef VARIANTMAPTABLEMODEL_H
#define VARIANTMAPTABLEMODEL_H

#include <QAbstractTableModel>
#include <QObject>

class VariantMapTableModel;

//Abstract column class
class AbstractColumn
{
public:
    AbstractColumn(QString name, QString caption = "");
    virtual ~AbstractColumn();
    QString name() { return _name; }
    QString caption() { return _caption; }
    virtual QVariant colData(const QVariantMap &rowData, int role = Qt::DisplayRole) = 0;
private:
    QString _name;
    QString _caption;
};

//Default column implementation
class SimpleColumn : public AbstractColumn
{
public:
    SimpleColumn(QString name, QString caption = "");

    // AbstractColumn interface
public:
    virtual QVariant colData(const QVariantMap &rowData, int role) override;
};

class LookupColumn : public AbstractColumn
{
public:
    LookupColumn(QString name, VariantMapTableModel* model, QString keyCol, QString lookupCol);
protected:
    VariantMapTableModel* _lookupModel;
    QString _keyColumn;
    QString _lookupColumn;
    // AbstractColumn interface
public:
    virtual QVariant colData(const QVariantMap &rowData, int role) override;
};

class VariantMapTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    VariantMapTableModel(QObject *parent = nullptr);
    void registerColumn(AbstractColumn* column);
    void registerColumn(QString name, QString caption = "");
    void addRow(QVariantMap rowData);
    void deleteByRow(int row);
    void clear();
    QVariant data(int row, QString colName);

    //Convenience methods
    int idByRow(int row) const;
    int rowById(int id) const;
    int colByName(QString name) const;
    QString nameByCol(int col) const;
private:
    //Storing data members
    QList<int> _rowIndex;
    QHash<int, QVariantMap> _dataHash;
    QList<AbstractColumn*> _columns;

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    // QAbstractItemModel interface
public:
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    // QAbstractItemModel interface
public:
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

#endif // VARIANTMAPTABLEMODEL_H
