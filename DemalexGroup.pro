TEMPLATE = subdirs

SUBDIRS += \
	DemalexManager.pro \
        plugins/FIREBIRD/FirebirdPlugin.pro \
        plugins/MYSQL/MysqlPlugin.pro \
        plugins/SQLITE/SqlitePlugin.pro \
        plugins/POSTGRES/PostgresPlugin.pro

CONFIG += qt
