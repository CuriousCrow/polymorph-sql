#ifndef QKNOWLEDGEBASE_H
#define QKNOWLEDGEBASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include "models/lsqltablemodel.h"
#include "models/ldbobjecttablemodel.h"

class QKnowledgeBase : public QObject
{
  Q_OBJECT
public:
  explicit QKnowledgeBase(QObject *parent = nullptr);
  ~QKnowledgeBase();

  static QKnowledgeBase* kb(QObject* parent = nullptr);
  LSqlTableModel* mKeywords;
  LSqlTableModel* mFunctions;
  LSqlTableModel* mTypes;

  void loadModels(const QStringList &drivers);
  LDBObjectTableModel* modelByType(QString type, QString driver = "");
  void loadModelByType(QString table, QString type, QString driver = "");

  QHash<int, QString> typesHash(QString dbms);
  QString typeName(int type);
  int typeByName(QString dbms, QString name);
private:
  static QKnowledgeBase* _kb;
  QHash<QString, LDBObjectTableModel*> _modelHash;
signals:

public slots:
};

#endif // QKNOWLEDGEBASE_H
