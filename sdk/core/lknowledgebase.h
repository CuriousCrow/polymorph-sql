#ifndef LKNOWLEDGEBASE_H
#define LKNOWLEDGEBASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include "../models/lsqltablemodel.h"
#include "../models/ldbobjecttablemodel.h"

class LKnowledgeBase : public QObject
{
  Q_OBJECT
public:
  Q_INVOKABLE LKnowledgeBase(QObject *parent = nullptr);
  ~LKnowledgeBase();

  LSqlTableModel* mTypes;

  void loadModels(const QStringList &drivers);
  LDBObjectTableModel* modelByType(QString type, QString driver = "");
  void loadModelByType(QString table, QString type, QString driver = "");

  QHash<int, QString> typesHash(QString dbms);
  QString typeName(int type);
  int typeByName(QString dbms, QString name);
private:
  QHash<QString, LDBObjectTableModel*> _modelHash;
signals:

public slots:
};

#endif // LKNOWLEDGEBASE_H
