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
	dbms TEXT NOT NULL, 
	name TEXT NOT NULL, 
	caption TEXT
);

--T_TABLE_COLUMNS
CREATE TABLE "t_table_columns" (
    "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    "database_id" INTEGER NOT NULL,
    "tablename" TEXT NOT NULL,
    "state" BLOB,
	UNIQUE(database_id, tablename)
);

--Data
--T_FUNCTIONS
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('2', 'abs', '[integer|smallint|numeric|real]', 'absolute value', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('3', 'cbrt', '[dp]', 'cube root', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('4', 'ceil', '[dp|numeric]', 'nearest integer greater than or equal to argument', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('5', 'ceiling', '[dp|numeric]', 'nearest integer greater than or equal to argument ', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('6', 'degrees', '[dp]', 'radians to degrees', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('7', 'div', '[numeric],[numeric]', 'integer quotient of y/x', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('8', 'exp', '[dp|numeric]', 'exponential', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('9', 'floor', '[dp|numeric]', 'nearest integer less than or equal to argument', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('10', 'ln', '[dp|numeric]', 'natural logarithm', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('11', 'log', '[dp|numeric]', 'base 10 logarithm', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('12', 'log', '[b numeric, x numeric]', 'logarithm to base b', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('13', 'mod', '[y],[x]', 'remainder of y/x', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('14', 'pi', '', '"π" constant', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('15', 'power', '[a dp, b dp]', 'a raised to the power of b', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('16', 'radians', '[dp]', ' 	degrees to radians', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('17', 'round', '[dp|numeric]', 'round to nearest integer', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('18', 'sign', 'dp|numeric', 'sign of the argument (-1, 0, +1)', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('19', 'sqrt', 'dp|numeric', 'square root', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('20', 'trunc', 'dp|numeric', 'truncate toward zero', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('21', 'random', '', 'random value in the range 0.0 <= x < 1.0', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('22', 'acos', '[x]', 'inverse cosine', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('23', 'asin', '[x]', 'inverse sine', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('24', 'atan', '[x]', 'inverse tangent', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('25', 'atan2', '[y],[x]', 'inverse tangent of y/x', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('26', 'cos', '[x]', 'cosine', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('27', 'cot', '[x]', 'cotangent', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('28', 'sin', '[x]', 'sine', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('29', 'tan', '[x]', 'tangent', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('30', 'bit_length', '', 'Number of bits in string', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('31', 'char_length', '', 'Number of characters in string', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('32', 'lower', '[string]', 'Convert string to lower case', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('33', 'octet_length', '', 'Number of bytes in string', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('34', 'overlay', '', 'Replace substring', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('35', 'position', '', 'Location of specified substring', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('36', 'substring', '', 'Extract substring', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('37', 'trim', '[string]', 'Remove the longest string containing only characters from characters', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('38', 'upper', '[string]', 'Convert string to upper case', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('39', 'length', '[string]', 'Number of characters in string', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('40', 'md5', '[string]', 'Calculates the MD5 hash of string, returning the result in hexadecimal', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('41', 'regexp_matches', '', 'Return all captured substrings resulting from matching a POSIX regular expression against the string. ', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('42', 'regexp_replace', '', 'Replace substring(s) matching a POSIX regular expression. ', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('43', 'repeat', '', 'Repeat string the specified number of times', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('44', 'replace', '', 'Replace all occurrences in string of substring from with substring to', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('45', 'reverse', '[string]', 'Return reversed string.', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('46', 'left', '[string]', 'Return first n characters in the string. When n is negative, return all but last |n| characters.', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('47', 'right', '[string]', 'Return last n characters in the string. When n is negative, return all but first |n| characters.', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('48', 'ltrim', '[string]', 'Remove the longest string containing only characters from characters (a space by default) from the start of string', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('49', 'rtrim', '[string]', 'Remove the longest string containing only characters from characters (a space by default) from the end of string', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');

--T_KEYWORDS
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('1', 'select', 'select - is a basic SQL keyword', 'https://www.postgresql.org/docs/9.5/sql-select.html', 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('2', 'from', '<b>FROM</b> - is a very good word', NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('3', 'where', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('4', 'order', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('5', 'insert', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('6', 'update', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('7', 'delete', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('8', 'create', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('9', 'drop', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('10', 'table', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('11', 'view', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('12', 'index', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('13', 'by', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('14', 'and', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('15', 'or', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('16', 'in', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('17', 'into', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('18', 'case', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('19', 'coalesce', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('20', 'count', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('21', 'alter', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('22', 'left', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('23', 'join', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('24', 'right', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('25', 'inner', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('26', 'for', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('27', 'like', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('28', 'min', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('29', 'max', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('30', 'exists', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('31', 'set', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('32', 'sum', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('33', 'with', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('34', 'lock', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('35', 'having', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('36', 'outer', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('37', 'trim', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('38', 'trigger', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('39', 'procedure', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('40', 'sequence', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('41', 'column', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('42', 'add', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('43', 'null', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('44', 'constraint', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('45', 'unique', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('46', 'not', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('47', 'then', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('48', 'end', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('49', 'on', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('50', 'full', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('51', 'asc', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('52', 'ascending', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('53', 'desc', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('54', 'descending', NULL, NULL, 'QPSQL');

--T_TYPES
insert into t_types ("id", "dbms", "name", "caption") values ('1', 'QSQLITE', 'INTEGER', 'Integer');
insert into t_types ("id", "dbms", "name", "caption") values ('2', 'QSQLITE', 'TEXT', 'Text');
insert into t_types ("id", "dbms", "name", "caption") values ('3', 'QSQLITE', 'REAL', 'Real');
insert into t_types ("id", "dbms", "name", "caption") values ('4', 'QSQLITE', 'BLOB', 'Blob');
insert into t_types ("id", "dbms", "name", "caption") values ('5', 'QPSQL', 'BOOLEAN', 'Boolean');
insert into t_types ("id", "dbms", "name", "caption") values ('6', 'QPSQL', 'SMALLINT', 'SmallInt');
insert into t_types ("id", "dbms", "name", "caption") values ('7', 'QPSQL', 'INTEGER', 'Integer');
insert into t_types ("id", "dbms", "name", "caption") values ('8', 'QPSQL', 'BIGINT', 'BigInt');
insert into t_types ("id", "dbms", "name", "caption") values ('9', 'QPSQL', 'DATE', 'Date');
insert into t_types ("id", "dbms", "name", "caption") values ('10', 'QPSQL', 'TIMESTAMP', 'Timestamp');
insert into t_types ("id", "dbms", "name", "caption") values ('11', 'QPSQL', 'CHARACTER VARYING', 'Varchar');
insert into t_types ("id", "dbms", "name", "caption") values ('12', 'QPSQL', 'TIME', 'Time');
insert into t_types ("id", "dbms", "name", "caption") values ('13', 'QPSQL', 'REAL', 'Real');
insert into t_types ("id", "dbms", "name", "caption") values ('14', 'QPSQL', 'CHAR', 'Char');
insert into t_types ("id", "dbms", "name", "caption") values ('15', 'QPSQL', 'NUMERIC', 'Numeric');
insert into t_types ("id", "dbms", "name", "caption") values ('16', 'QIBASE', 'VARCHAR', 'Varchar');
insert into t_types ("id", "dbms", "name", "caption") values ('17', 'QIBASE', 'CHAR', 'Char');
insert into t_types ("id", "dbms", "name", "caption") values ('18', 'QIBASE', 'INTEGER', 'Integer');
insert into t_types ("id", "dbms", "name", "caption") values ('19', 'QIBASE', 'BIGINT', 'BigInt');
insert into t_types ("id", "dbms", "name", "caption") values ('20', 'QIBASE', 'DATE', 'Date');
insert into t_types ("id", "dbms", "name", "caption") values ('21', 'QIBASE', 'TIMESTAMP', 'Timestamp');
insert into t_types ("id", "dbms", "name", "caption") values ('22', 'QIBASE', 'SMALLINT', 'SmallInt');


