#ifndef QKNOWLEDGEBASE_H
#define QKNOWLEDGEBASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include "models/lsqltablemodel.h"

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

  QHash<int, QString> typesHash(QString dbms);
  QString typeName(int type);
  int typeByName(QString dbms, QString name);
private:
  static QKnowledgeBase* _kb;
signals:

public slots:
};

#endif // QKNOWLEDGEBASE_H
