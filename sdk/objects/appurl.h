#ifndef APPURL_H
#define APPURL_H

#include <QObject>

class AppUrl
{
public:
  AppUrl();
  AppUrl(const QString& strUrl);
  AppUrl(const QString& driver, const QString& database);
  bool isValid() const;
  bool isParent(const AppUrl &url) const;
  QString toString() const;
  AppUrl& cdUp();
  AppUrl& cd(QString name);
  AppUrl folderUrl(QString name);

  QString connection() const;

  void setPath(const QString &path = "");
  QString path() const;

  QString driver() const;
  void setDriver(const QString &driver);

  QString database() const;
  void setDatabase(const QString &database);

  friend QDataStream &operator<<(QDataStream &out, const AppUrl &url);
private:
  QString _driver;
  QString _database;
  QStringList _pathItems;
};

#endif // APPURL_H
