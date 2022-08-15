#ifndef ABSTRACTIDENTIFIERSUPPORT_H
#define ABSTRACTIDENTIFIERSUPPORT_H

#include <QString>

class AbstractIdentifierSupport
{
public:
  virtual QString escapeIdentifier(QString ident) = 0;
};

class NoOpIdentifier : public AbstractIdentifierSupport
{
public:
  virtual QString escapeIdentifier(QString ident);
};

class QuoteIdentifier : public AbstractIdentifierSupport
{
public:
  virtual QString escapeIdentifier(QString ident);
};

class BacktickIdentifier : public AbstractIdentifierSupport
{
public:
  virtual QString escapeIdentifier(QString ident);
};

#endif // ABSTRACTIDENTIFIERSUPPORT_H
