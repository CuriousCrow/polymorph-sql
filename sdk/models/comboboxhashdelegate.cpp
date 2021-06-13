#include "comboboxhashdelegate.h"
#include <QComboBox>
#include <QDebug>

ComboboxHashDelegate::ComboboxHashDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}

void ComboboxHashDelegate::setItemsHash(QHash<int, QString> valHash)
{
  _itemsHash = valHash;
}

void ComboboxHashDelegate::insertValuePair(int key, QString text)
{
  _itemsHash.insert(key, text);
}

void ComboboxHashDelegate::clear()
{
  _itemsHash.clear();
}

QWidget *ComboboxHashDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  Q_UNUSED(option)
  Q_UNUSED(index)
  qDebug() << "create delegate editor";
  QComboBox* combobox = new QComboBox(parent);
  foreach (int key, _itemsHash.keys()) {
    combobox->addItem(_itemsHash.value(key), key);
  }
  return combobox;
}

void ComboboxHashDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  QComboBox* combo = qobject_cast<QComboBox*>(editor);
  combo->setCurrentText(index.data().toString());
}

void ComboboxHashDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  QComboBox* combo = qobject_cast<QComboBox*>(editor);
  model->setData(index, combo->currentData());
}

void ComboboxHashDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  Q_UNUSED(index)
  editor->setGeometry(option.rect);
}
