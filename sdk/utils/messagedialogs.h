#ifndef MESSAGEDIALOGS_H
#define MESSAGEDIALOGS_H

#include <QObject>
#include "objects/appconst.h"

class MessageDialogs
{
public:
  static void info(QString message, QString title = TITLE_INFO);
  static void warn(QString message, QString title = TITLE_WARNING);
  static void error(QString message, QString title = TITLE_ERROR);
};

#endif // MESSAGEDIALOGS_H
