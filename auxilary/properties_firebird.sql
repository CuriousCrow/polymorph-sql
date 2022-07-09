--Data

--T_TYPES
insert into t_types ("id", "dbms", "name", "caption") values ('400', 'QIBASE', 'VARCHAR', 'Varchar');
insert into t_types ("id", "dbms", "name", "caption") values ('401', 'QIBASE', 'CHAR', 'Char');
insert into t_types ("id", "dbms", "name", "caption") values ('402', 'QIBASE', 'INTEGER', 'Integer');
insert into t_types ("id", "dbms", "name", "caption") values ('403', 'QIBASE', 'BIGINT', 'BigInt');
insert into t_types ("id", "dbms", "name", "caption") values ('404', 'QIBASE', 'DATE', 'Date');
insert into t_types ("id", "dbms", "name", "caption") values ('405', 'QIBASE', 'TIMESTAMP', 'Timestamp');
insert into t_types ("id", "dbms", "name", "caption") values ('406', 'QIBASE', 'SMALLINT', 'SmallInt');

--T_KEYWORDS
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('401', 'select', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('402', 'from', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('403', 'where', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('404', 'order', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('405', 'insert', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('406', 'update', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('407', 'delete', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('408', 'create', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('409', 'drop', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('410', 'table', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('411', 'view', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('412', 'index', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('413', 'by', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('414', 'and', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('415', 'or', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('416', 'in', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('417', 'into', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('418', 'case', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('419', 'coalesce', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('420', 'count', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('421', 'alter', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('422', 'left', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('423', 'join', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('424', 'right', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('425', 'inner', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('426', 'for', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('427', 'like', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('428', 'min', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('429', 'max', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('430', 'exists', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('431', 'set', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('432', 'sum', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('433', 'with', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('434', 'lock', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('435', 'having', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('436', 'outer', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('437', 'trim', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('438', 'trigger', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('439', 'procedure', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('440', 'sequence', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('441', 'column', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('442', 'add', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('443', 'null', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('444', 'constraint', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('445', 'unique', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('446', 'not', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('447', 'then', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('448', 'end', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('449', 'on', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('450', 'full', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('451', 'asc', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('452', 'ascending', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('453', 'desc', NULL, NULL, 'QIBASE');
insert into t_keywords ("id", "name", "description", "doclink", "driver") values ('454', 'descending', NULL, NULL, 'QIBASE');

