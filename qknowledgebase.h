#ifndef QKNOWLEDGEBASE_H
#define QKNOWLEDGEBASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>


class QKnowledgeBase : public QObject
{
  Q_OBJECT
public:
  explicit QKnowledgeBase(QObject *parent = 0);
  ~QKnowledgeBase();

  static QKnowledgeBase* kb(QObject* parent = 0);
  QSqlTableModel* mKeywords;
private:
  static QKnowledgeBase* _kb;
signals:

public slots:
};

#endif // QKNOWLEDGEBASE_H
