#ifndef FIREBIRDUTILS_H
#define FIREBIRDUTILS_H

#include <QString>

/** Utility functions for Firebird plugin */
class Utils
{
private:
  Utils();
public:
  static QString typeFromCode(int code);
};

#endif // FIREBIRDUTILS_H
