#include "include/common.h"
using namespace std;

/*The Grammar:
    CREATE TABLE TABLE_NAME;*/
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
//129.211.69.209@
//root
//Hhcl199904020
SAConnection* hfts_db::con=nullptr;
int hfts_db::init_db(char* host_name,char* user_name,char* pwd,char* db_name){
    //connect to the database
    try {
        #ifdef DEBUG
        cout<<"host_name"<<host_name<<" user name "<<user_name<<" pwd "<<pwd<<" db_name "<<db_name<<endl;
        #endif
        con=new SAConnection();
        get_connection()->Connect(host_name, user_name, pwd, SA_MySQL_Client);

    }
    catch(SAException &x) {
        get_connection()->Rollback();
        printf("%s\n", x.ErrText().GetMultiByteChars());
        if(x.ErrNativeCode()==CONNECTION_TIME_OUT){
            log_error("Connection time out,please check your internet connection");
        }
    }

    //select the database
    try {
        SACommand select(get_connection(), db_name);
        select.Execute();
    } catch (SAException x) {
        get_connection()->Rollback();
        printf("%s\n", x.ErrText().GetMultiByteChars());
    }

    //test the result
    if(get_connection()->isConnected()){
        log_error("Connect to the data base success");
        return 0;
    }else return -1;
}
//shutdown the database connection
int hfts_db::shutdown_db(){
    try {
        if(get_connection()->isConnected())get_connection()->Disconnect();
    }
    catch(SAException &x) {
        get_connection()->Rollback();
        printf("%s\n", x.ErrText().GetMultiByteChars());
    }
    if(!get_connection()->isConnected()){
        cout<<"Shutdown success"<<endl;
        return 0;
    }
    log_error("An error occurred while disconnecting the database");
    return -1;
}
int hfts_db::read_db(){
    if(!get_connection()->isConnected()){
        cout<<"not alive"<<endl;
    }
    SACommand select(get_connection(), _TSA("SELECT * FROM TEST"));
    select.Execute();
    try{
        while(select.FetchNext()) {
        //Add the code below
        /*
        double age = select[1].asDouble();
        SAString name = select[2].asString();
        printf("age:%f,name:%s",age,name.GetMultiByteChars());
        */
        }
    }
    catch(SAException &x){
        get_connection()->Rollback();
        printf("%s\n", x.ErrText().GetMultiByteChars());
        return -1;
    }
    return 0;
}
//simply execute a command
int hfts_db::execute_cmd(char* cmd){
    SACommand select(get_connection(), _TSA(cmd));
    try{
        select.Execute();
    }catch(SAException &e){
        cout<<e.ErrText().GetMultiByteChars();
        return -1;
    }
    return 0;
}

//check if the table already exist
bool hfts_db::is_table_exist(char* table_name){
    if(!get_connection()->isConnected()){
        log_error("error:the database is not alive");
        return -1;
    }
    SACommand select_tb(get_connection(), _TSA("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME=:1"));
    select_tb<<_TSA(table_name);

    try{
        select_tb.Execute();
    }catch (SAException &e){
        cout<<e.ErrText().GetMultiByteChars();
    }

    if(select_tb.FetchNext())return true;
    else return false;
}


//create the future contract
//Check if the contract exists in the database,if not create one.
int hfts_db::create_contract(char* contract_name){
    if(!is_table_exist(contract_name)){
        log_info("The contract table does not exist,now registering a new one");
        char final_cmd[100];
        sprintf(final_cmd,"CREATE TABLE %s(UPDATE_TIME DATETIME(3),LAST_PRICE DOUBLE,ASK_PRICE DOUBLE,ASK_VOLUME DOUBLE,BID_PRICE DOUBLE,BID_VOLUME DOUBLE,OPEN_INTEREST DOUBLE,TURN_OVER DOUBLE,PRIMARY KEY(UPDATE_TIME))",contract_name);
        SACommand create_tb(get_connection(),final_cmd);
        try{
            create_tb.Execute();
        }
        catch(SAException &x){
            get_connection()->Rollback();
            printf("%s\n", x.ErrText().GetMultiByteChars());
        }
    }
}
//create the index table in index_name
int hfts_db::create_index(char* index_name){
    if(!is_table_exist(index_name)){
        char final_cmd[100];
        sprintf(final_cmd,"CREATE TABLE %s(UPDATE_TIME DATETIME(3),LAST_PRICE DOUBLE,PRIMARY KEY(UPDATE_TIME))",index_name);
        SACommand create_tb(get_connection(),final_cmd);
        try{
            create_tb.Execute();
        }
        catch(SAException &x){
            get_connection()->Rollback();
            printf("%s\n", x.ErrText().GetMultiByteChars());
            return -1;
        }
    }
    return 0;
}
//insert the market data.
int hfts_db::insert_depth_db(CThostFtdcDepthMarketDataField *data){
    char prepare_cmd[500];
    sprintf(prepare_cmd,"INSERT INTO %s (UPDATE_TIME,LAST_PRICE,ASK_PRICE,ASK_VOLUME,BID_PRICE,BID_VOLUME,OPEN_INTEREST,TURN_OVER) VALUES (:1,:2,:3,:4,:5,:6,:7,:8)",data->InstrumentID);
    //YYYY-MM-DD HH:MM:SS
    SADateTime update_date_time(get_year(data->TradingDay),get_mon(data->TradingDay),get_day(data->TradingDay),get_hour(data->UpdateTime),get_min(data->UpdateTime),get_sec(data->UpdateTime),data->UpdateMillisec*1000000);
    SACommand insert_data(get_connection(),prepare_cmd);
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
        printf("%s\n", e.ErrText().GetMultiByteChars());
    }
    
}
int hfts_db::insert_index_data(index_t index_type,index_eledata e){
    char* index_name[4]={"shangzheng50","zhongzheng500","hushen300"};
    char prepare_cmd[500];
    sprintf(prepare_cmd,"INSERT INTO %s (UPDATE_TIME,LAST_PRICE) VALUES (:1,:2)",index_name[index_type]);
    SACommand insert_data(get_connection(),prepare_cmd);
    insert_data<<e.time
               <<(double)e.value;
    try{
        insert_data.Execute();
    }
    catch (SAException &e){
        printf("%s\n", e.ErrText().GetMultiByteChars());
    }
}
