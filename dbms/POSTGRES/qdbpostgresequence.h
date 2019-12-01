#ifndef QDBPOSTGRESEQUENCE_H
#define QDBPOSTGRESEQUENCE_H

#include <QObject>
#include "../qdbsequenceitem.h"

class DBPostgreSequence : public DBSequenceItem
{
  Q_OBJECT
public:
  DBPostgreSequence(QString caption, QObject* parent = nullptr);

  // QDBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // QDBPOSTGRESEQUENCE_H
