#ifndef QDBVIEWITEM_H
#define QDBVIEWITEM_H

#include "qdbtableitem.h"

class QDBViewItem : public QDBTableItem
{
  Q_OBJECT
  Q_PROPERTY(QString queryText READ queryText WRITE setQueryText)
public:
  QDBViewItem(QString caption, QObject* parent = 0);
  ~QDBViewItem();

  QString queryText() const;
  void setQueryText(const QString &queryText);

private:
  QString _queryText;

  // LAbstractTreeItem interface
public:
  virtual int colCount();
  virtual QVariant colData(int column, int role);
  virtual bool setData(int column, QVariant value, int role);
  // QDBObjectItem interface
public:
  virtual int type();
  virtual bool deleteMe();

  // QDBTableItem interface
public:
  virtual void reloadColumnsModel();
};

#endif // QDBVIEWITEM_H
