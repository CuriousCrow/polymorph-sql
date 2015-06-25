#include "ldatawidgetmapper.h"
#include <QAbstractItemModel>
#include <QWidget>

LDataWidgetMapper::LDataWidgetMapper(QObject *parent):
  QDataWidgetMapper(parent)
{
  connect(this, SIGNAL(currentIndexChanged(int)),
          SLOT(updateReadOnlyWidgets(int)));
}

LDataWidgetMapper::~LDataWidgetMapper()
{
}

void LDataWidgetMapper::updateReadOnlyWidgets(int row)
{
  int sectionCount = model()->columnCount(rootIndex());
  for (int i=0; i<sectionCount; i++){
    QWidget* widget = mappedWidgetAt(i);
    if (widget){
      widget->setEnabled(model()->flags(model()->index(row, i, rootIndex())).testFlag(Qt::ItemIsEditable));
    }
  }
}

