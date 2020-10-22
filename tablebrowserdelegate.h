#ifndef TABLEBROWSERDELEGATE_H
#define TABLEBROWSERDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include "models/unisqltablemodel.h"
#include "dbms/dbtableitem.h"

class TableBrowserDelegate : public QStyledItemDelegate
{
  Q_OBJECT
public:
  TableBrowserDelegate(DBTableItem* tableItem, QObject *parent = nullptr);

  // QAbstractItemDelegate interface
public:
  virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
  virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
  virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
  DBTableItem* _tableItem;
  UniSqlTableModel* _foreignTable;
  QMap<int, QString> _foreignKeys;
private slots:
  void onValueSelected(const QModelIndex &index);
};

#endif // TABLEBROWSERDELEGATE_H
