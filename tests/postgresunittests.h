#ifndef SQLITEUNITTESTS_H
#define SQLITEUNITTESTS_H

#include <QObject>
#include <QtTest>
#include <QCoreApplication>

#include "core/core.h"

class PostgresUnitTests : public QObject
{
  Q_OBJECT
public:
  PostgresUnitTests(QObject *parent = nullptr);
  ~PostgresUnitTests();

private slots:
  void initTestCase();
  void cleanupTestCase();

  void postgresViewTest();
  void postgresTableTest();
  void postgresPrimaryKeyTest();
  void postgresUniqueTest();
  void postgresSequenceTest();
//  void postgresForeignKeyTest();

private:
  Core* _core;
};

#endif // SQLITEUNITTESTS_H
