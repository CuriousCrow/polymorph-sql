#ifndef QDBTABLEITEM_H
#define QDBTABLEITEM_H

#include "qdbobjectitem.h"
#include "models/sqlcolumnmodel.h"


class QDBTableItem : public QDBObjectItem
{
  Q_OBJECT
public:
  QDBTableItem(QString caption, QObject* parent = nullptr);
  virtual ~QDBTableItem() override;
  virtual void reloadColumnsModel();
  QAbstractTableModel* columnsModel();
  int colTypeFromString(QString name);
  void addDefaultColumn();
//  QHash<int, QString> getColumnTypesHash();

  // QDBObjectItem interface
public:
  virtual bool loadChildren() override;
  virtual int type() override;

  // LAbstractTreeItem interface
public:
  virtual int colCount() override;
  virtual QVariant colData(int column, int role) override;

  // QDBObjectItem interface
public:
  virtual ActionResult deleteMe() override;
  virtual ActionResult updateMe() override;
protected:
  SqlColumnModel* _columnsModel;
};

#endif // QDBTABLEITEM_H
