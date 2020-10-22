#include "tablebrowserdelegate.h"
#include <QTableView>
#include "dbms/appconst.h"
#include <QDebug>


TableBrowserDelegate::TableBrowserDelegate(DBTableItem* tableItem, QObject *parent)
  : QStyledItemDelegate(parent), _tableItem(tableItem)
{
  _foreignTable = new UniSqlTableModel(this, QSqlDatabase::database(tableItem->connectionName()));
  QAbstractTableModel* constraints = _tableItem->constraintsModel();
  for(int i=0; i<constraints->rowCount(); i++) {
    QString type = constraints->data(constraints->index(i, 0)).toString();
    QString name = constraints->data(constraints->index(i, 1)).toString();
    qDebug() << name << type;
    if (type == "FOREIGN KEY") {
      DBForeignKey* item = _tableItem->loadForeignKey(name);
      QString colName = item->fieldValue(F_COLUMN).toString();
      QString refTable = item->fieldValue(F_REFTABLE).toString();

      int colIdx = _tableItem->columnsModel()->rowByName(colName);
      qDebug() << "Foreign key:" << colIdx << colName << refTable;
      _foreignKeys.insert(colIdx, refTable);
    }
  }
}

QWidget *TableBrowserDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  if (_foreignKeys.contains(index.column())) {
    QTableView* editor = new QTableView(parent);
    editor->setAutoFillBackground(true);
    editor->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(editor, &QTableView::doubleClicked, this, &TableBrowserDelegate::onValueSelected);
    _foreignTable->setTable(_foreignKeys.value(index.column()));
    _foreignTable->select();
    editor->setModel(_foreignTable);
    return editor;
  }
  return QStyledItemDelegate::createEditor(parent, option, index);
}

void TableBrowserDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  if (_foreignKeys.contains(index.column())) {

  }
  else {
    return QStyledItemDelegate::setEditorData(editor, index);
  }
}

void TableBrowserDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  if (_foreignKeys.contains(index.column())) {
    QTableView* editorView = qobject_cast<QTableView*>(editor);
    model->setData(index, _foreignTable->idByRow(editorView->currentIndex().row()));
  }
  else {
    QStyledItemDelegate::setModelData(editor, model, index);
  }
}

void TableBrowserDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  if (_foreignKeys.contains(index.column())) {
    QRect rect(option.rect.left(), option.rect.top(), 200, 200);
    editor->setGeometry(rect);
  }
  else {
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
  }
}

void TableBrowserDelegate::onValueSelected(const QModelIndex &index)
{
  Q_UNUSED(index)

  QTableView* editor = qobject_cast<QTableView*>(sender());
  emit commitData(editor);
  emit closeEditor(editor);
}
