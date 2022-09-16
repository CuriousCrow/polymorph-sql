TEMPLATE = subdirs

SUBDIRS += \
  PolymorphManager.pro \
  plugins/FIREBIRD/FirebirdPlugin.pro \
  plugins/MYSQL/MysqlPlugin.pro \
  plugins/SQLITE/SqlitePlugin.pro \
  plugins/POSTGRES/PostgresPlugin.pro
#  SqliteTests.pro \
#  PostgresTests.pro

CONFIG += qt
