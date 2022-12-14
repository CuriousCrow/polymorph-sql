#include "comboboxitemdelegate.h"
#include <QComboBox>
#include <QDebug>


ComboboxItemDelegate::ComboboxItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void ComboboxItemDelegate::setOptions(QStringList list)
{
  _options = list;
}

QWidget *ComboboxItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  Q_UNUSED(option)
  Q_UNUSED(index)

  qDebug() << "create delegate editor";
  QComboBox* combobox = new QComboBox(parent);
  combobox->addItems(_options);
  return combobox;
}

void ComboboxItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  QComboBox* combo = static_cast<QComboBox*>(editor);
  combo->setCurrentText(index.data().toString());
}

void ComboboxItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  QComboBox* combo = static_cast<QComboBox*>(editor);
  model->setData(index, combo->currentText());
}

void ComboboxItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  Q_UNUSED(option)
  Q_UNUSED(index)
  editor->setGeometry(option.rect);
}
