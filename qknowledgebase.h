#ifndef QKNOWLEDGEBASE_H
#define QKNOWLEDGEBASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include "lsqltablemodel.h"


class QKnowledgeBase : public QObject
{
  Q_OBJECT
public:
  explicit QKnowledgeBase(QObject *parent = nullptr);
  ~QKnowledgeBase();

  static QKnowledgeBase* kb(QObject* parent = nullptr);
  LSqlTableModel* mKeywords;
private:
  static QKnowledgeBase* _kb;
signals:

public slots:
};

#endif // QKNOWLEDGEBASE_H
