#ifndef QDBSTRUCTUREMODEL_H
#define QDBSTRUCTUREMODEL_H

#include <QObject>
#include "../../Qt/LSqlTableModel/trunk/lsqltreemodel.h"

class QDBStructureModel : public LSqlTreeModel
{
  Q_OBJECT
public:
  explicit QDBStructureModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());
  ~QDBStructureModel();

signals:

public slots:

public:
  void addItem(qlonglong id, QString name, int type, qlonglong parentId = 0);
  virtual QVariant data(const QModelIndex &index, int role) const;
};

#endif // QDBSTRUCTUREMODEL_H
