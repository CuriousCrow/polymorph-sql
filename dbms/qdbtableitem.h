#ifndef QDBTABLEITEM_H
#define QDBTABLEITEM_H

#include "qdbobjectitem.h"
#include "models/sqlcolumnmodel.h"
#include "models/variantmaptablemodel.h"
#include "qdbforeignkey.h"

class QDBTableItem : public QDBObjectItem
{
  Q_OBJECT
public:
  QDBTableItem(QString caption, QObject* parent = nullptr);
  virtual ~QDBTableItem() override;
  virtual void reloadColumnsModel();
  virtual void reloadConstraintsModel();

  QAbstractTableModel* columnsModel();
  QAbstractTableModel* constraintsModel();

  virtual QDBForeignKey* newForeignKey();

  int colTypeFromString(QString name);
  void addDefaultColumn();
//  QHash<int, QString> getColumnTypesHash();

  // LAbstractTreeItem interface
public:
  virtual int colCount() override;
  virtual QVariant colData(int column, int role) override;

  // QDBObjectItem interface
public:
  virtual bool loadChildren() override;
  virtual int type() override;

  virtual ActionResult updateMe() override;
  virtual ActionResult deleteMe() override;

  virtual bool isModified() override;
protected:
  SqlColumnModel* _columnsModel;
  VariantMapTableModel* _constraintsModel;
};

#endif // QDBTABLEITEM_H
