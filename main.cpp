#include "include/common.h"
#include "include/main.h"
#include <iostream>
#include <unistd.h>
using namespace std;



int main(){
#ifdef DEBUG
	cout<<"now in the debug mode"<<endl;
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
	trade_api->RegisterFront(td_front_addr);
	market_api->RegisterFront(md_front_addr);
}
void menu(){
	
	key_type key;
	log_str("Please input your choice");
	cin>>key;
	switch(key){
		case '1':
			;
		default:
			log_str("You input");log_str(key);
			break;
	}
}
void menu_view(){
	cout<<"The version info:"<<trade_api->GetApiVersion()<<endl;
	cout<<"The trading day:"<<trade_api->GetTradingDay()<<endl;
	log_str("\tMENU\t",GREEN_STR);
	log_str("1.Show the market bulletin",GREEN_STR);
	log_str("2.Configure the strategy",GREEN_STR);
	log_str("3.Start the analysis and auto-trade",GREEN_STR);
	cout<<endl;
}

