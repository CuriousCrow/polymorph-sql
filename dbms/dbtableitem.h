#ifndef DBTABLEITEM_H
#define DBTABLEITEM_H

#include "dbobjectitem.h"
#include "models/sqlcolumnmodel.h"
#include "models/variantmaptablemodel.h"
#include "dbforeignkey.h"

class DBTableItem : public DBObjectItem
{
  Q_OBJECT
public:
  DBTableItem(QString caption, QObject* parent = nullptr);
  virtual ~DBTableItem() override;
  virtual void reloadColumnsModel();
  virtual void reloadConstraintsModel();

  QAbstractTableModel* columnsModel();
  QAbstractTableModel* constraintsModel();

  virtual DBForeignKey* newForeignKey();

  int colTypeFromString(QString name);
  void addDefaultColumn();
//  QHash<int, QString> getColumnTypesHash();

  // LAbstractTreeItem interface
public:
  virtual int colCount() override;
  virtual QVariant colData(int column, int role) override;

  // DBObjectItem interface
public:
  virtual bool reloadChildren() override;
  virtual int type() override;

  virtual ActionResult updateMe() override;
  virtual ActionResult deleteMe() override;

  virtual bool isModified() override;
protected:
  SqlColumnModel* _columnsModel;
  VariantMapTableModel* _constraintsModel;
};

#endif // DBTABLEITEM_H