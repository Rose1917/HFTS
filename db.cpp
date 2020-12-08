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
//Check if the contract exists in the database,if not create one.
int create_contract(char* contract_name){
    //To check if this contract_name already exist.
    //execute_cmd("USE INFORMATION_SCHEMA");
    if(!con.isConnected()){
        cout<<"not alive"<<endl;
    }
    SACommand select_tb(&con, _TSA("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME=:1"));
    select_tb<<_TSA(contract_name);
    select_tb.Execute();
    if(select_tb.FetchNext()){
        //it already exists.
        log_info("Already exists");
        return 0;
    }
    //TODO:change the table directory
    /*
	log_str("Instrument ID:",data->InstrumentID,GREEN_STR,1);
	log_str("Trading Day:",data->TradingDay,GREEN_STR,1);
	log_str("Update time:",data->UpdateTime,GREEN_STR,1);
	log_str("Update mills:",int2c(data->UpdateMillisec),GREEN_STR,1);
	log_str("Last Price:",double2c(data->LastPrice),GREEN_STR,1);
	log_str("Ask Price:",double2c(data->AskPrice1),GREEN_STR,1);
	log_str("Ask Volume:",double2c(data->AskVolume1),GREEN_STR,1);
	log_str("Bid Price:",double2c(data->BidPrice1),GREEN_STR,1);
	log_str("Bid Volume:",double2c(data->BidVolume1),GREEN_STR,1);
	log_str("OpenInterest:",double2c(data->OpenInterest),GREEN_STR,1);
	log_str("Turn Over:",double2c(data->Turnover),GREEN_STR,1);
    */
    else {
        log_info("The contract table does not exist,now registering a new one");
        char final_cmd[100];
        sprintf(final_cmd,"CREATE TABLE %s(UPDATE_TIME DATETIME(3),LAST_PRICE DOUBLE,ASK_PRICE DOUBLE,ASK_VOLUME DOUBLE,BID_PRICE DOUBLE,BID_VOLUME DOUBLE,OPEN_INTEREST DOUBLE,TURN_OVER DOUBLE,PRIMARY KEY(UPDATE_TIME))",contract_name);
        SACommand create_tb(&con,final_cmd);
        try{
            create_tb.Execute();
        }
        catch(SAException &x){
            con.Rollback();
            printf("%s\n", x.ErrText().GetMultiByteChars());
    }
    }
}
int create_index(char* index_name){
    if(!con.isConnected()){
        cout<<"not alive"<<endl;
    }
    SACommand select_tb(&con, _TSA("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME=:1"));
    select_tb<<_TSA(index_name);
    select_tb.Execute();
    if(select_tb.FetchNext()){
        //it already exists.
        log_info("Already exists");
        return 0;
    }
    else {
        log_info("The index table does not exist,now registering a new one");
        char final_cmd[100];
        sprintf(final_cmd,"CREATE TABLE %s(UPDATE_TIME DATETIME(3),LAST_PRICE DOUBLE,PRIMARY KEY(UPDATE_TIME))",index_name);
        SACommand create_tb(&con,final_cmd);
        try{
            create_tb.Execute();
        }
        catch(SAException &x){
            con.Rollback();
            printf("%s\n", x.ErrText().GetMultiByteChars());
        }
    }
}

void insert_depth_db(CThostFtdcDepthMarketDataField *data){
    char prepare_cmd[500];
    sprintf(prepare_cmd,"INSERT INTO %s (UPDATE_TIME,LAST_PRICE,ASK_PRICE,ASK_VOLUME,BID_PRICE,BID_VOLUME,OPEN_INTEREST,TURN_OVER) VALUES (:1,:2,:3,:4,:5,:6,:7,:8)",data->InstrumentID);
    //YYYY-MM-DD HH:MM:SS
    SADateTime update_date_time(get_year(data->TradingDay),get_mon(data->TradingDay),get_day(data->TradingDay),get_hour(data->UpdateTime),get_min(data->UpdateTime),get_sec(data->UpdateTime),data->UpdateMillisec*1000000);
    cout<<"frac"<<update_date_time.Fraction()<<endl;
    SACommand insert_data(&con,prepare_cmd);
    insert_data<<update_date_time
               <<(double)data->LastPrice
               <<(double)data->AskPrice1
               <<(double)data->AskVolume1
               <<(double)data->BidPrice1
               <<(double)data->BidVolume1
               <<(double)data->OpenInterest
               <<(double)data->Turnover;
    try{
        insert_data.Execute();
    }
    catch (SAException &e){
        cout<<"The Instrument ID:"<<data->InstrumentID<<endl;
        printf("%s\n", e.ErrText().GetMultiByteChars());
        cout<<"Millsec: "<<data->UpdateMillisec<<endl;
    }
    
}
int insert_index_data(){
    
}