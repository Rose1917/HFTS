#include "include/common.h"
using namespace std;
SAConnection con;
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
int init_db(){
	 try {
        con.Connect(_TSA("129.211.69.209@"), _TSA("root"), _TSA("Hhcl199904020"), SA_MySQL_Client);
        execute_cmd("USE HFTS");
    }
    catch(SAException &x) {
        log_error("An error occurred while initing the database");
        con.Rollback();
        printf("%s\n", x.ErrText().GetMultiByteChars());
    }

    if(con.isConnected()){
        log_error("Connect to the data base success");
        return 0;
    }else return -1;
}
int shutdown_db(){
    try {
        if(con.isConnected())con.Disconnect();
        else return 0;
    }
    catch(SAException &x) {
        con.Rollback();
        printf("%s\n", x.ErrText().GetMultiByteChars());
    }
    if(!con.isConnected()){
        cout<<"Shutdown success"<<endl;
        return 0;
    }
    return -1;
}
void read_db(){
    if(!con.isConnected()){
        cout<<"not alive"<<endl;
    }
    SACommand select(&con, _TSA("SELECT * FROM TEST"));
    select.Execute();
    try{
        while(select.FetchNext()) {
        double age = select[1].asDouble();
        SAString name = select[2].asString();
        printf("age:%f,name:%s",age,name.GetMultiByteChars());
        }
    }
    catch(SAException &x){
        con.Rollback();
        printf("%s\n", x.ErrText().GetMultiByteChars());
    }
}
void execute_cmd(char* cmd){
    SACommand select(&con, _TSA(cmd));
    select.Execute();
}
int create_contract(char* contract_name){
    //To check if this contract_name already exist.
    //execute_cmd("USE INFORMATION_SCHEMA");
    if(!con.isConnected()){
        cout<<"not alive"<<endl;
    }
    SACommand select_tb(&con, _TSA("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME=:1"));
    select_tb<<_TSA(contract_name);
    cout<<&(*(select_tb.CommandText()));
    select_tb.Execute();
    if(select_tb.FetchNext()){
        //it already exists.
        log_info("Already exists");
        return 0;
    }
    else {
        log_info("The contract table does not exist,now 
        char final_cmd[50];
        sprintf(final_cmd,"CREATE TABLE %s(AGE INT(4),NAME VARCHAR(10))",contract_name);
        SACommand create_tb(&con,final_cmd);
        create_tb.Execute();
    }
}