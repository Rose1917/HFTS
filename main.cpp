#include "include/common.h"
#include <iostream>
#include <unistd.h>
using namespace std;

//Global variables
api* trade_api=nullptr;
md_api* market_api=nullptr;
econf_ptr econf=nullptr;

int main(){
#ifdef DEBUG
	cout<<"now under the debug mode:"<<endl;
#endif
	init();
	sleep(5);
	menu();
	return 0;
}
void init(){	
	trade_api=api::CreateFtdcTraderApi("./info/");
	market_api=md_api::CreateFtdcMdApi("./market_info/");
	
	extend_spi* trade_spi=new extend_spi(trade_api);
	trade_api->RegisterSpi(trade_spi);
	extend_md_spi* market_spi=new extend_md_spi(market_api);
	market_api->RegisterSpi(market_spi);
	
	register_front();
	trade_api->SubscribePrivateTopic(THOST_TERT_QUICK);
	trade_api->SubscribePublicTopic(THOST_TERT_QUICK);	

	trade_api->Init();
	market_api->Init();
}
void register_front(){
	econf=new env_config("tcp://180.168.146.187:10101","tcp://180.168.146.187:10131");
	trade_api->RegisterFront(econf->get_td_front_addr());
	market_api->RegisterFront(econf->get_md_front_addr());
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
void menu_view(){
	system("clear");
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

