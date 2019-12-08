#ifndef MYSQLPLUGIN_H
#define MYSQLPLUGIN_H

#include <QObject>
#include "../dbmsplugin.h"

class MysqlPlugin : public DbmsPlugin
{
public:
  MysqlPlugin();

  // DbmsPlugin interface
public:
  virtual QString driver() override;
  virtual DBDatabaseItem *newDatabaseItem(QString caption, QObject *parent) override;
  virtual DBTableItem *newTableItem(QString caption, QObject *parent) override;
  virtual DBViewItem *newViewItem(QString caption, QObject *parent) override;
  virtual DBProcedureItem *newProcedureItem(QString caption, QObject *parent) override;
  virtual DBSequenceItem *newSequenceItem(QString caption, QObject *parent) override;
  virtual DBTriggerItem *newTriggerItem(QString caption, QObject *parent) override;
  virtual AbstractDatabaseEditForm *formByType(DBObjectItem::ItemType type) override;
};

#endif // MYSQLPLUGIN_H
