#ifndef SIMPLECACHEDTABLEMODEL_H
#define SIMPLECACHEDTABLEMODEL_H

#include <QAbstractTableModel>

class CacheField
{
public:
  CacheField(QString name, QVariant initValue = QVariant());
  QString name();
  void setValue(QVariant val);
  QVariant value();
  QVariant oldValue();

  void revert();

private:
  QString _name;
  bool _modified;
  QVariant _oldValue;
  QVariant _value;
};

class CacheRowObject
{
public:
  CacheRowObject();
  QVariant fieldValue(int idx);
  QVariant fieldValue(QString field);
  void setValue(int idx, QVariant val);
  void setValue(QString field, QVariant val);
  int count() const;
  CacheField* field(int idx) const;
protected:
  void registerField(CacheField* field);
private:
  QList<CacheField*> _fields;
  int fieldIdxByName(QString field);
};

class SimpleCachedTableModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  SimpleCachedTableModel(CacheRowObject sampleRow, QObject *parent = Q_NULLPTR);

  void addRow(CacheRowObject* rowObj);
public:
  virtual int rowCount(const QModelIndex &parent) const;
  virtual int columnCount(const QModelIndex &parent) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

public slots:
  virtual bool submit();
  virtual void revert();

private:
  CacheRowObject _sampleRowObj;
  QList<CacheRowObject*> _rows;
};

#endif // SIMPLECACHEDTABLEMODEL_H
