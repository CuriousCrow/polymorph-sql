#ifndef SQLITEUNITTESTS_H
#define SQLITEUNITTESTS_H

#include <QObject>
#include <QtTest>
#include <QCoreApplication>

#include "core/core.h"

class SqliteUnitTests : public QObject
{
  Q_OBJECT
public:
  SqliteUnitTests(QObject *parent = nullptr);
  ~SqliteUnitTests();

private slots:
  void initTestCase();
  void cleanupTestCase();

  void sqliteViewTest();
  void sqliteTableTest();

private:
  Core* _core;
};

#endif // SQLITEUNITTESTS_H
