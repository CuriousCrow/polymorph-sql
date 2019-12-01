#include "appurl.h"
#include <QDebug>
#include <QDataStream>

#define URL_DELIMITER "/"

AppUrl::AppUrl()
{
}

AppUrl::AppUrl(const QString &strUrl) : AppUrl()
{
  QRegExp rx("^([\\w]+):\\/\\/([\\w_]+)(?:\\/([\\w\\/_]+))?$");
  bool match = rx.exactMatch(strUrl);
  if (match) {
    _driver = rx.cap(1);
    _database = rx.cap(2);
    setPath(rx.cap(3));
  }
}

AppUrl::AppUrl(const QString &driver, const QString &database)
  : _driver(driver), _database(database)
{
}

bool AppUrl::isValid() const
{
  return !_driver.isEmpty() && !_database.isEmpty();
}

bool AppUrl::isParent(const AppUrl &url) const
{
  qDebug() << this->toString() << url.toString();
  return this->toString().contains(url.toString());
}

QString AppUrl::toString() const
{
  QString pattern = "%1://%2";
  QString url = pattern.arg(_driver).arg(_database);
  if (!_pathItems.isEmpty())
    url.append(URL_DELIMITER).append(_pathItems.join(URL_DELIMITER));
  return url;
}

AppUrl &AppUrl::cdUp()
{
  if (!_pathItems.isEmpty())
    _pathItems.removeLast();
  return *this;
}

AppUrl &AppUrl::cd(QString name)
{
  if (name.isEmpty()) {
    qWarning() << "Empty name in cd()";
  }
  else {
    _pathItems.append(name);
  }
  return *this;
}

AppUrl AppUrl::folderUrl(QString name)
{
  AppUrl newUrl = *this;
  newUrl.setPath(name);
  return newUrl;
}

QString AppUrl::connection() const
{
  if (!isValid()) {
    qWarning() << "Empty connection name";
    return "";
  }
  AppUrl dbUrl(*this);
  dbUrl.setPath();
  return dbUrl.toString();
}

QString AppUrl::path() const
{
  return _pathItems.join(URL_DELIMITER);
}

void AppUrl::setPath(const QString &path)
{
  _pathItems = path.split(URL_DELIMITER, QString::SkipEmptyParts);
}

QString AppUrl::driver() const
{
  return _driver;
}

void AppUrl::setDriver(const QString &driver)
{
  _driver = driver;
}

QString AppUrl::database() const
{
  return _database;
}

void AppUrl::setDatabase(const QString &database)
{
  _database = database;
}


QDataStream &operator<<(QDataStream &out, const AppUrl &url)
{
  out.setVersion(QDataStream::Qt_4_7);
  out << url.toString();
  return out;
}
