CREATE TABLE "t_database" (
    "ID" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    "NAME" TEXT NOT NULL,
    "DRIVER" TEXT NOT NULL,
    "HOST_ADDRESS" TEXT,
    "LOCAL_PATH" TEXT,
    "USERNAME" TEXT,
    "PASSWORD" TEXT
);

CREATE TABLE "t_functions" (
	id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
	name TEXT NOT NULL, 
	args TEXT, 
	description TEXT DEFAULT a, 
	doclink TEXT DEFAULT a, 
	driver TEXT
);

CREATE TABLE "t_keywords" (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
	name TEXT NOT NULL, 
	description TEXT, 
	doclink TEXT, 
	driver TEXT NOT NULL
);

CREATE TABLE "t_query_history" (
    "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    "database_id" INTEGER NOT NULL,
    "query" TEXT NOT NULL
);

CREATE TABLE "t_settings" (
    "key" TEXT NOT NULL,
    "value" TEXT NOT NULL,
    "defvalue" TEXT NOT NULL
);

CREATE TABLE t_types (
	id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
	driver TEXT NOT NULL, 
	name TEXT NOT NULL, 
	caption TEXT,
	description TEXT,
	doclink TEXT,
	kind TEXT
);

--T_TABLE_COLUMNS
CREATE TABLE "t_table_columns" (
    "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    "database_id" INTEGER NOT NULL,
    "tablename" TEXT NOT NULL,
    "state" BLOB,
	UNIQUE(database_id, tablename)
);




