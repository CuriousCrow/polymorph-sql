#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <qdbstructuremodel.h>
#include "connectioneditdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_aAddDatabase_triggered();

  void on_aEditDatabase_triggered();

  void on_tvDatabaseStructure_doubleClicked(const QModelIndex &index);

private:
  Ui::MainWindow *ui;
  QSqlDatabase appDB;
  QMap<qlonglong, QSqlDatabase> databasePool;
  QDBStructureModel* mDbStructure;
  QSqlTableModel* mDatabases;
  QSqlTableModel* mTables;
  ConnectionEditDialog* connectionEditDialog;
  void initDatabaseItems();
  void loadDatabaseItems(qlonglong dbId);
  QVariant tableData(QSqlTableModel* model, int row, QString field);
  int databaseRowById(qlonglong id);
};

#endif // MAINWINDOW_H
