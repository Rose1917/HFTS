#include "include/common.h"
#include "login.h"
#include <QApplication>
#include <iostream>
#include <unistd.h>
using namespace std;

//Global variables
api* trade_api=nullptr;
md_api* market_api=nullptr;
econf_ptr econf=nullptr;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();

#ifdef DEBUG
	cout<<"now under the debug mode:"<<endl;
#endif
	
	//init();
	//sleep(5);
	//menu();
	//create_contract("ag2012");
	//share_index ix(SHANGZHENG_50,0);
	
	//ix.update_val();
	//ix1.update_val();
	//ix2.update_val();
	//cout<<ix.get_index_val()<<ix1.get_index_val()<<ix1.get_index_val()<<endl;
	//index_strategy indddx;
	//init_db();
	//share_index ix(SHANGZHENG_50,1.1);
	//ix.update_val();
	//market_init();

	market_init();
	login_market(nullptr,nullptr);
	
	trader_init();
	login_trader(string("177050"),string("3650599367aA"));
	
	CThostFtdcInputOrderField f;
	strcpy(f.BrokerID,econf->get_broker_id());
	strcpy(f.InvestorID,econf->get_investor_id());
	strcpy(f.ExchangeID,env_config::local_exchange_id[ZHONGJINSUO]);

	//order_handler::insert_order(&f,0);


    cout<<"test1"<<endl;
    a.exec();
	return 0;

}
//asychronorous front connection 
int market_init(){
	//Got the configuration object
	log_str("=====INIT THE DATABASE=====",YELLOW_STR);
	econf=new env_config();
	econf->set_md_front_addr("tcp://180.168.146.187:10110");
	econf->set_md_front_addr(env_config::local_md_config[LINK3]);

	//connect to the database	
	hfts_db::init_db(econf->get_host_name(),econf->get_db_user(),econf->get_db_pwd(),econf->get_db_name());

	log_str("=====INIT THE MARKET API=====",YELLOW_STR);
    market_api=md_api::CreateFtdcMdApi("./market_info/");
	extend_md_spi* market_spi=new extend_md_spi(market_api);
	market_api->RegisterSpi(market_spi);
	market_api->RegisterFront(econf->get_md_front_addr());
	market_api->Init();
	//wait the front connected.
	system_status::wait_code_till_true(MARKET_FRONT);
}

int trader_init(){

	log_str("=====INIT THE TRADE API=====",YELLOW_STR);
	trade_api=api::CreateFtdcTraderApi("./info/");
	extend_spi* trade_spi=new extend_spi(trade_api);
	trade_api->RegisterSpi(trade_spi);
	trade_api->RegisterFront(econf->get_td_front_addr());
	
	trade_api->SubscribePrivateTopic(THOST_TERT_QUICK);
	trade_api->SubscribePublicTopic(THOST_TERT_QUICK);
	trade_api->Init();
	system_status::wait_code_till_true(TRADER_FRONT);
}
int req_authenticate(string broker_id,string user_id,string app_id,string authen_code){
	
	CThostFtdcReqAuthenticateField auth_field;
	memset(&auth_field,0,sizeof(auth_field));
	strcpy(auth_field.BrokerID,"9999");
	strcpy(auth_field.UserID,"177050");
	strcpy(auth_field.AppID,"simnow_client_test");
	strcpy(auth_field.AuthCode,"0000000000000000");

	log_stone(1);
	//Authenticate
	trade_api->ReqAuthenticate(&auth_field,0);
	system_status::wait_code_till_true(AUTHENTICATION);
}
int login_trader(string user_name,string pwd){
	//Authenticate before logging in
	req_authenticate(string("9999"),string("177050"),string("simnow_client_test"),string("0000000000000000"));

	CThostFtdcReqUserLoginField login_field;
	strcpy(login_field.BrokerID,"9999");
	strcpy(login_field.UserID,"177050");
	strcpy(login_field.Password,"3650599367aA");
	
	//to-do
	trade_api->ReqUserLogin(&login_field,0);
	system_status::wait_code_till_true(TRADER_LOGIN);

	//set the id into the memmory
	econf->set_broker_id(login_field.BrokerID);
	econf->set_investor_id(login_field.UserID);
}

void menu(){
	print_version();
	key_type key;
	while(true){
		menu_view();
		cin>>key;
		switch(key){
			case '1':show_data();break;
			case '4':hide_data();break;
			case '5':order_main();break;
			case '6':load_doc("helper.txt");break;
			case '0':exit(0);break;
			
			default:
				print_prompt();break;
				break;
		}
	}
	
}
//asynchronorous login request
int login_market(char* user_name,char* pwd){
	CThostFtdcReqUserLoginField login_field;
	string broker_id="9999";
	string user_id="177050";
	string user_pwd="3650599367aA";

	strcpy(login_field.BrokerID,broker_id.data());
	strcpy(login_field.UserID,user_id.data());
	strcpy(login_field.Password,user_pwd.data());
	
	market_api->ReqUserLogin(&login_field,0);
	system_status::wait_code_till_true(MARKET_LOGIN);
	econf->set_investor_id(user_id.data());
	econf->set_broker_id(broker_id.data());	

}
int subsribe_market_data(char* instr_id){
	market_api->SubscribeMarketData(&instr_id,1);
}
void menu_view(){
	//system("clear");
	log_str("\tMENU\t",GREEN_STR);
	log_str("1.Show the market bulletin",GREEN_STR);
	log_str("2.Configure the strategy",GREEN_STR);
	log_str("3.Start the analysis and auto-trade",GREEN_STR);
	log_str("4.Stopping the market bulletin",GREEN_STR);
	log_str("5.place an order",GREEN_STR);
	log_str("6.help",GREEN_STR);
	log_str("0.exit",GREEN_STR);

	cout<<":";
}
void print_version(){
	cout<<"CTP version info:"<<trade_api->GetApiVersion()<<endl;
	cout<<"The trading day:"<<trade_api->GetTradingDay()<<endl;
}
void print_prompt(){
	cout<<"You have input an illegal command"<<endl;
	cout<<"Input 6 for more infomation"<<endl;
}
void load_doc(char* doc_name){
	ifstream rs;
	char prefix[50]="doc/";
	strcat(prefix,doc_name);
	rs.open(prefix);
	if(!rs.is_open()){
		log_error("log doc:an error occurred while loading the doc file",doc_name);
		exit(0);
	}
	int line=1;
	string buffer;

	int page_size=econf->get_page_size();
	string key;
	while(getline(rs,buffer)){
		if(page_size==0){
			cout<<":";
			cin>>key;
			if(key=="q")return ;
			else{
				page_size=econf->get_page_size();
			}
		}
		cout<<(line++)<<"\t"<<buffer<<endl;
		page_size--;
	}
	sleep(5);
}

