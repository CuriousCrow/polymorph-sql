#ifndef UNISQLTABLEFILTERACTION_H
#define UNISQLTABLEFILTERACTION_H

#include <QAction>
#include <QObject>
#include <QListView>
#include "utils/sqlfiltermanager.h"

class UniSqlTableFilterAction : public QAction
{
  Q_OBJECT
public:
  Q_INVOKABLE UniSqlTableFilterAction();
  void setView(QListView* view);
protected:
  SqlFilterManager* _filterModel;
  QListView* _listView;
};

#endif // UNISQLTABLEFILTERACTION_H
