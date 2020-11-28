#ifndef DB_H
#define DB_H
/*CREATE TABLE TABLE_NAME;*/
/*USE TABLE_NAME*/
/*

CREATE TABLE TEST(
AGE INT`TEST`(4),
NAME VARCHAR(10)
);
--
*/
/*
-- DROP TABLE TEST;
-- SHOW TABLES;
/*CREATE TABLE TEST(
AGE FLOAT(4,2),
NAME VARCHAR(10)
);*/
/*
-- INSERT INTO TEST VALUES(4.2,'ZHAOMOU');
-- COMMIT;
-- SELECT * FROM TEST;
*/
int init_db();
int shutdown_db();
void read_db();
void execute_cmd(char* cmd);
int create_contract(char* contract_name);
#endif