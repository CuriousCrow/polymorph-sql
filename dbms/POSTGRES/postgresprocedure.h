#ifndef POSTGRESPROCEDURE_H
#define POSTGRESPROCEDURE_H

#include <QObject>
#include "../dbprocedureitem.h"

class PostgresProcedure : public DBProcedureItem
{
  Q_OBJECT
public:
  PostgresProcedure(QString caption, QObject* parent = nullptr);
};

#endif // POSTGRESPROCEDURE_H
