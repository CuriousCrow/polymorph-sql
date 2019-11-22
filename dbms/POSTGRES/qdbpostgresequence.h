#ifndef QDBPOSTGRESEQUENCE_H
#define QDBPOSTGRESEQUENCE_H

#include <QObject>
#include "../qdbsequenceitem.h"

class QDBPostgreSequence : public QDBSequenceItem
{
  Q_OBJECT
public:
  QDBPostgreSequence(QString caption, QUrl url, QObject* parent = nullptr);

  // QDBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // QDBPOSTGRESEQUENCE_H
