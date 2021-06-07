#ifndef DBTABLEITEM_H
#define DBTABLEITEM_H

#include "dbselectableitem.h"
#include "models/sqlcolumnmodel.h"
#include "models/variantmaptablemodel.h"
#include "dbforeignkey.h"
#include "dbuniqueconstraint.h"
#include "dbcheckconstraint.h"
#include "dbprimarykey.h"

class DBTableItem : public DBSelectableItem
{
  Q_OBJECT
public:
  Q_INVOKABLE DBTableItem();
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

  // DBObjectItem interface
public:
  virtual int type() const Q_DECL_OVERRIDE;

  virtual ActionResult updateMe() Q_DECL_OVERRIDE;
  virtual ActionResult deleteMe() Q_DECL_OVERRIDE;
  virtual bool refresh() Q_DECL_OVERRIDE;
  virtual QString toDML() const Q_DECL_OVERRIDE;

  virtual bool isModified() const Q_DECL_OVERRIDE;
protected:
  SqlColumnModel* _columnsModel;
  VariantMapTableModel* _constraintsModel;

};

#endif // DBTABLEITEM_H
