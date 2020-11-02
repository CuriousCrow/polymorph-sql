#ifndef DBTABLEITEM_H
#define DBTABLEITEM_H

#include "dbobjectitem.h"
#include "models/sqlcolumnmodel.h"
#include "models/variantmaptablemodel.h"
#include "dbforeignkey.h"
#include "dbuniqueconstraint.h"
#include "dbcheckconstraint.h"
#include "dbprimarykey.h"

class DBTableItem : public DBObjectItem
{
  Q_OBJECT
public:
  DBTableItem(QString caption, QObject* parent = nullptr);
  virtual ~DBTableItem() Q_DECL_OVERRIDE;
  virtual void reloadColumnsModel();
  virtual void reloadConstraintsModel();

  SqlColumnModel* columnsModel();
  QAbstractTableModel* constraintsModel();

  virtual DBForeignKey* newForeignKey();
  virtual DBPrimaryKey* newPrimaryKey();
  virtual DBUniqueConstraint* newUniqueConstraint();
  virtual DBCheckConstraint* newCheckConstraint();

  DBForeignKey* loadForeignKey(QString name);

  int colTypeFromString(QString name);
  void addDefaultColumn();
//  QHash<int, QString> getColumnTypesHash();

  // LAbstractTreeItem interface
public:
  virtual int colCount() const Q_DECL_OVERRIDE;
  virtual QVariant colData(int column, int role) const Q_DECL_OVERRIDE;

  // DBObjectItem interface
public:
  virtual bool reloadChildren() Q_DECL_OVERRIDE;
  virtual int type() const Q_DECL_OVERRIDE;

  virtual ActionResult updateMe() Q_DECL_OVERRIDE;
  virtual ActionResult deleteMe() Q_DECL_OVERRIDE;
  virtual QString toDML() const Q_DECL_OVERRIDE;

  virtual bool isModified() const Q_DECL_OVERRIDE;
protected:
  SqlColumnModel* _columnsModel;
  VariantMapTableModel* _constraintsModel;

};

#endif // DBTABLEITEM_H
