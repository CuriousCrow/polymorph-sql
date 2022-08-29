#ifndef LKNOWLEDGEBASE_H
#define LKNOWLEDGEBASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include "models/lsqltablemodel.h"
#include "models/ldbobjecttablemodel.h"

struct TypeInfo
{
  QString name;
  QString caption;
  QString description;
  QString kind;
};

class LKnowledgeBase : public QObject
{
  Q_OBJECT
public:
  Q_INVOKABLE LKnowledgeBase(QObject *parent = nullptr);
  ~LKnowledgeBase();

  void loadModels(const QStringList &drivers);
  LDBObjectTableModel* modelByType(QString type, QString driver = "");
  void loadModelByType(QString table, QString type, QString driver = "");

  QHash<int, QString> typesHash(QString dbms);
  QString typeName(int type);
  int typeByName(QString dbms, QString name);

  void loadTypeModel(QString driver);
  LDBObjectTableModel* typesByDriver(QString driver);
private:
  LSqlTableModel* _mTypes;
  QHash<QString, LDBObjectTableModel*> _modelHash;
  QHash<QString, LDBObjectTableModel*> _typesHash;
signals:

public slots:
};

#endif // LKNOWLEDGEBASE_H
