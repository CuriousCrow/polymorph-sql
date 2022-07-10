--Data

--T_TYPES
insert into t_types ("id", "dbms", "name", "caption") values ('100', 'QPSQL', 'BOOLEAN', 'Boolean');
insert into t_types ("id", "dbms", "name", "caption") values ('101', 'QPSQL', 'SMALLINT', 'SmallInt');
insert into t_types ("id", "dbms", "name", "caption") values ('102', 'QPSQL', 'INTEGER', 'Integer');
insert into t_types ("id", "dbms", "name", "caption") values ('103', 'QPSQL', 'BIGINT', 'BigInt');
insert into t_types ("id", "dbms", "name", "caption") values ('104', 'QPSQL', 'DATE', 'Date');
insert into t_types ("id", "dbms", "name", "caption") values ('105', 'QPSQL', 'TIMESTAMP', 'Timestamp');
insert into t_types ("id", "dbms", "name", "caption") values ('106', 'QPSQL', 'CHARACTER VARYING', 'Varchar');
insert into t_types ("id", "dbms", "name", "caption") values ('107', 'QPSQL', 'TIME', 'Time');
insert into t_types ("id", "dbms", "name", "caption") values ('108', 'QPSQL', 'REAL', 'Real');
insert into t_types ("id", "dbms", "name", "caption") values ('109', 'QPSQL', 'CHAR', 'Char');
insert into t_types ("id", "dbms", "name", "caption") values ('110', 'QPSQL', 'NUMERIC', 'Numeric');
insert into t_types ("id", "dbms", "name", "caption") values ('111', 'QPSQL', 'UUID', 'UUID');

--T_FUNCTIONS
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('102', 'abs', '[integer|smallint|numeric|real]', 'absolute value', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('103', 'cbrt', '[dp]', 'cube root', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('104', 'ceil', '[dp|numeric]', 'nearest integer greater than or equal to argument', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('105', 'ceiling', '[dp|numeric]', 'nearest integer greater than or equal to argument ', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('106', 'degrees', '[dp]', 'radians to degrees', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('107', 'div', '[numeric],[numeric]', 'integer quotient of y/x', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('108', 'exp', '[dp|numeric]', 'exponential', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('109', 'floor', '[dp|numeric]', 'nearest integer less than or equal to argument', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('110', 'ln', '[dp|numeric]', 'natural logarithm', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('111', 'log', '[dp|numeric]', 'base 10 logarithm', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('112', 'log', '[b numeric, x numeric]', 'logarithm to base b', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('113', 'mod', '[y],[x]', 'remainder of y/x', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('114', 'pi', '', '"π" constant', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('115', 'power', '[a dp, b dp]', 'a raised to the power of b', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('116', 'radians', '[dp]', ' 	degrees to radians', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('117', 'round', '[dp|numeric]', 'round to nearest integer', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('118', 'sign', 'dp|numeric', 'sign of the argument (-1, 0, +1)', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('119', 'sqrt', 'dp|numeric', 'square root', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('120', 'trunc', 'dp|numeric', 'truncate toward zero', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('121', 'random', '', 'random value in the range 0.0 <= x < 1.0', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('122', 'acos', '[x]', 'inverse cosine', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('123', 'asin', '[x]', 'inverse sine', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('124', 'atan', '[x]', 'inverse tangent', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('125', 'atan2', '[y],[x]', 'inverse tangent of y/x', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('126', 'cos', '[x]', 'cosine', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('127', 'cot', '[x]', 'cotangent', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('128', 'sin', '[x]', 'sine', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('129', 'tan', '[x]', 'tangent', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('130', 'bit_length', '', 'Number of bits in string', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('131', 'char_length', '', 'Number of characters in string', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('132', 'lower', '[string]', 'Convert string to lower case', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('133', 'octet_length', '', 'Number of bytes in string', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('134', 'overlay', '', 'Replace substring', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('135', 'position', '', 'Location of specified substring', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('136', 'substring', '', 'Extract substring', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('137', 'trim', '[string]', 'Remove the longest string containing only characters from characters', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('138', 'upper', '[string]', 'Convert string to upper case', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('139', 'length', '[string]', 'Number of characters in string', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('140', 'md5', '[string]', 'Calculates the MD5 hash of string, returning the result in hexadecimal', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('141', 'regexp_matches', '', 'Return all captured substrings resulting from matching a POSIX regular expression against the string. ', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('142', 'regexp_replace', '', 'Replace substring(s) matching a POSIX regular expression. ', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('143', 'repeat', '', 'Repeat string the specified number of times', NULL, 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('144', 'replace', '', 'Replace all occurrences in string of substring from with substring to', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('145', 'reverse', '[string]', 'Return reversed string.', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('146', 'left', '[string]', 'Return first n characters in the string. When n is negative, return all but last |n| characters.', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('147', 'right', '[string]', 'Return last n characters in the string. When n is negative, return all but first |n| characters.', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('148', 'ltrim', '[string]', 'Remove the longest string containing only characters from characters (a space by default) from the start of string', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');
insert into t_functions ("id", "name", "args", "description", "doclink", "driver") values ('149', 'rtrim', '[string]', 'Remove the longest string containing only characters from characters (a space by default) from the end of string', 'https://www.postgresql.org/docs/9.5/functions-string.html#FUNCTIONS-STRING-SQL', 'QPSQL');

--T_KEYWORDS
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('101', 'select', 'select - is a basic SQL keyword', 'https://www.postgresql.org/docs/9.5/sql-select.html', 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('102', 'from', '<b>FROM</b> - is a very good word', NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('103', 'where', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('104', 'order', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('105', 'insert', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('106', 'update', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('107', 'delete', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('108', 'create', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('109', 'drop', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('110', 'table', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('111', 'view', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('112', 'index', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('113', 'by', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('114', 'and', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('115', 'or', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('116', 'in', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('117', 'into', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('118', 'case', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('119', 'coalesce', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('120', 'count', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('121', 'alter', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('122', 'left', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('123', 'join', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('124', 'right', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('125', 'inner', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('126', 'for', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('127', 'like', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('128', 'min', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('129', 'max', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('130', 'exists', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('131', 'set', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('132', 'sum', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('133', 'with', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('134', 'lock', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('135', 'having', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('136', 'outer', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('137', 'trim', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('138', 'trigger', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('139', 'procedure', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('140', 'sequence', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('141', 'column', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('142', 'add', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('143', 'null', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('144', 'constraint', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('145', 'unique', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('146', 'not', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('147', 'then', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('148', 'end', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('149', 'on', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('150', 'full', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('151', 'asc', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('152', 'ascending', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('153', 'desc', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('154', 'descending', NULL, NULL, 'QPSQL');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('155', 'distinct', NULL, NULL, 'QPSQL');