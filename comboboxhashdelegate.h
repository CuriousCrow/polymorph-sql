#ifndef COMBOBOXHASHDELEGATE_H
#define COMBOBOXHASHDELEGATE_H

#include <QStyledItemDelegate>

class ComboboxHashDelegate : public QStyledItemDelegate
{
  Q_OBJECT
public:
  ComboboxHashDelegate(QObject *parent = Q_NULLPTR);
  void setItemsHash(QHash<int, QString> valHash);
  void insertValuePair(int key, QString text);
  void clear();
  // QAbstractItemDelegate interface
public:
  virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
  virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
  virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
  QHash<int, QString> _itemsHash;
};

#endif // COMBOBOXHASHDELEGATE_H
