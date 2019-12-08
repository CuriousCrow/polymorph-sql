#ifndef FIREBIRDPLUGIN_H
#define FIREBIRDPLUGIN_H

#include <QObject>
#include "../dbmsplugin.h"


class FirebirdPlugin : public DbmsPlugin
{
public:
  FirebirdPlugin();

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

#endif // FIREBIRDPLUGIN_H
