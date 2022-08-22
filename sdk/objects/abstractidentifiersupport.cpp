#include "abstractidentifiersupport.h"


QString QuoteIdentifier::escapeIdentifier(QString ident)
{
  QString res = ident;
  if(!ident.isEmpty() && !ident.startsWith(QLatin1Char('"')) && !ident.endsWith(QLatin1Char('"')) ) {
      res.replace(QLatin1Char('"'), QLatin1String("\"\""));
      res.prepend(QLatin1Char('"')).append(QLatin1Char('"'));
      res.replace(QLatin1Char('.'), QLatin1String("\".\""));
  }
  return res;
}

QString BacktickIdentifier::escapeIdentifier(QString ident)
{
  QString res = ident;
  if(!ident.isEmpty() && !ident.startsWith(QLatin1Char('`')) && !ident.endsWith(QLatin1Char('`')) ) {
      res.replace(QLatin1Char('`'), QLatin1String("``"));
      res.prepend(QLatin1Char('`')).append(QLatin1Char('`'));
      res.replace(QLatin1Char('.'), QLatin1String("`.`"));
  }
  return res;
}

QString NoOpIdentifier::escapeIdentifier(QString ident)
{
  return ident;
}

AbstractIdentifierSupport::~AbstractIdentifierSupport()
{
}
