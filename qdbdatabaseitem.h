#ifndef QDBDATABASEITEM_H
#define QDBDATABASEITEM_H

#include "qdbobjectitem.h"
#include "qsqlqueryhelper.h"

class QDBDatabaseItem : public QDBObjectItem
{
  Q_OBJECT
  Q_PROPERTY(qlonglong id READ getId WRITE setId)
  Q_PROPERTY(QString hostName READ hostName WRITE setHostName)
  Q_PROPERTY(QString userName READ userName WRITE setUserName)
  Q_PROPERTY(QString password READ password WRITE setPassword)
  Q_PROPERTY(QString databaseName READ databaseName WRITE setDatabaseName)
  Q_PROPERTY(QString driverName READ driverName WRITE setDriverName)
public:
  QDBDatabaseItem(QString caption, QObject* parent = 0);
  ~QDBDatabaseItem();

  qlonglong getId() const;
  void setId(const qlonglong &value);

  QString hostName() const;
  void setHostName(const QString &hostName);

  QString userName() const;
  void setUserName(const QString &userName);

  QString password() const;
  void setPassword(const QString &password);

  QString databaseName() const;
  void setDatabaseName(const QString &databaseName);

  QString driverName() const;
  void setDriverName(const QString &driverName);

  bool createDbConnection();

private:
  qlonglong id;
  QString _driverName = "QSQLITE";
  QString _databaseName;
  QString _hostName;
  QString _userName;
  QString _password;
protected:
  QString fillSqlPattern(QString pattern);
  void loadSequenceItems(QDBObjectItem* parentItem);
  void loadTriggerItems(QDBObjectItem* parentItem);
  void loadProcedureItems(QDBObjectItem* parentItem);

  // QDBObjectItem interface
public:
  virtual bool loadChildren();
  virtual QUrl objectUrl();  
  virtual bool insertMe();
  virtual bool updateMe();
  virtual bool deleteMe();

  // LAbstractTreeItem interface
public:
  virtual int colCount();
  virtual QVariant colData(int column, int role);
  virtual int type();
  virtual bool setData(int column, QVariant value, int role);
};

#endif // QDBDATABASEITEM_H
