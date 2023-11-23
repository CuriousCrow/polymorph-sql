#include "tablebrowserdelegate.h"
#include <QTableView>
#include <QDebug>
#include "blobeditor.h"
#include "objects/appconst.h"

#define BLOB_COL -1 //Temperary disabled. Should be deleted when implementing uni-type item delegate


TableBrowserDelegate::TableBrowserDelegate(DBSelectableItem* item, QObject *parent)
  : QStyledItemDelegate(parent), _tableItem(item)
{
  _foreignTable = new UniSqlTableModel(this, item->connectionName());

  if (item->type() == DBObjectItem::Table) {
      DBTableItem* tableItem = static_cast<DBTableItem*>(item);
      QAbstractTableModel* constraints = tableItem->constraintsModel();
      for(int i=0; i<constraints->rowCount(); i++) {
        QString type = constraints->data(constraints->index(i, 0)).toString();
        QString name = constraints->data(constraints->index(i, 1)).toString();
        qDebug() << name << type;
        if (type == "FOREIGN KEY") {
          DBForeignKey* item = tableItem->loadForeignKey(name);
//          QString table = item->fieldValue(F_TABLE).toString();
          QString column = item->fieldValue(F_COLUMN).toString();
          QString refColumn = item->fieldValue(F_REFCOLUMN).toString();
          QString refTable = item->fieldValue(F_REFTABLE).toString();

          int colIdx = tableItem->columnsModel()->rowByName(column);
          if (colIdx >= 0) {
            qDebug() << "Foreign key:" << colIdx << column << refTable << refColumn;
            _foreignKeys.insert(colIdx, refTable);
          } else {
            qWarning() << "Can't define Foreign Key" << name << "column";
          }
        }
      }
  }

}

QWidget *TableBrowserDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  if (_foreignKeys.contains(index.column())) {
    QTableView* editor = new QTableView(parent);
    editor->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    editor->setAutoFillBackground(true);
    editor->setEditTriggers(QAbstractItemView::NoEditTriggers);
    editor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    editor->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    connect(editor, &QTableView::doubleClicked, this, &TableBrowserDelegate::onValueSelected);
    _foreignTable->setTable(_foreignKeys.value(index.column()));
    _foreignTable->select();
    editor->setModel(_foreignTable);
    return editor;
  }
  else if (index.column() == BLOB_COL) {
    qDebug() << "Blob delegate";
    BlobEditor* editor = new BlobEditor();
    return editor;
  }
  return QStyledItemDelegate::createEditor(parent, option, index);
}

void TableBrowserDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  qDebug() << "setEditorData() called";

  if (_foreignKeys.contains(index.column())) {

  }
  else if (index.column() == BLOB_COL) {
    static_cast<BlobEditor*>(editor)->setData(index.data().toByteArray());
  }
  else {
    return QStyledItemDelegate::setEditorData(editor, index);
  }
}

void TableBrowserDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  qDebug() << "setModelData() called";

  if (_foreignKeys.contains(index.column())) {
    QTableView* editorView = static_cast<QTableView*>(editor);
    model->setData(index, _foreignTable->primaryValue(editorView->currentIndex().row()));
  }
  else if (index.column() == BLOB_COL) {
    BlobEditor* blobEditor = static_cast<BlobEditor*>(editor);
    model->setData(index, blobEditor->data());
  }
  else {
    QStyledItemDelegate::setModelData(editor, model, index);
  }
}

void TableBrowserDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  if (_foreignKeys.contains(index.column())) {
    QPoint pos = editor->parentWidget()->mapToGlobal(editor->parentWidget()->pos());
    pos += option.rect.topLeft();
    QRect rect(pos.x(), pos.y(), 300, 200);
    editor->setGeometry(rect);
  }
  else {
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
  }
}

void TableBrowserDelegate::onValueSelected(const QModelIndex &index)
{
  Q_UNUSED(index)

  QTableView* editor = static_cast<QTableView*>(sender());
  emit commitData(editor);
  emit closeEditor(editor);
}
