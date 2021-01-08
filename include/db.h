#ifndef DB_H
#define DB_H
#include "common.h"
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

class hfts_db{
    static SAConnection *con;

    public:
    static int init_db(char* host_name,char* user_name,char* pwd,char* db_name);
    static int shutdown_db();
    static bool is_table_exist(char* table_name);
    static int read_db();
    static int execute_cmd(char*);
    static int create_contract(char*);
    static int create_index(char*);
    static int insert_depth_db(CThostFtdcDepthMarketDataField*);
    static int insert_index_data(index_t ,index_eledata);
    static SAConnection* get_connection(){return hfts_db::con;}
};
#endif
