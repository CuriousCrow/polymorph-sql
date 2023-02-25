#ifndef SDKUNITTESTS_H
#define SDKUNITTESTS_H

#include <QObject>
#include <QtTest>
#include <QCoreApplication>

#include "core/core.h"

class SdkUnitTests : public QObject
{
  Q_OBJECT
public:
  SdkUnitTests(QObject *parent = nullptr);

signals:

private slots:
  void initTestCase();
  void cleanupTestCase();

  //Test cases
  void ViewBasicTest();
  void TableBasicTest();
  void PrimaryKeyTest();
  void UniqueConstraintTest();
  void ForegnKeyTest();
  void CheckConstraintTest();
  void ProcedureDropTest();
  void TableDropTest();
private:
  Core* _core;
};

#endif // SDKUNITTESTS_H
