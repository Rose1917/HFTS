#include "include/common.h"
#include <iostream>
#include <unistd.h>
using namespace std;


//Configuration
string front_addr_str=string("tcp://180.168.146.187:10101");
char* front_addr=(char*) front_addr_str.data();

int main(){
#ifdef DEBUG
	cout<<"now in the debug mode"<<endl;
#endif
	//Step1.Get a trade api instance && a instance of market api.
	api* trade_api=api::CreateFtdcTraderApi("./info/");
	md_api* market_api=md_api::CreateFtdcMdApi("./market_info/");
	
	//Step2.Get a trade spi instance and register
	extend_spi* trade_spi=new extend_spi(trade_api);
	trade_api->RegisterSpi(trade_spi);
	
	
	//Step3.Register front
	//Group1-workday available only:
	//	trade front:180.168.146.187:10100
	//	market front:180.168.146.187:10100
	//Group2-7*24
	//	trade front:180.168.146.187:10130
	//	market front:180.168.146.187:10131
	trade_api->RegisterFront(front_addr);
	

	//subcribe the public stream
	/*参数解释：
	 *THOST_TERT_RESTART:从本交易日开始重传
	 *THOST_TERT_RESUME:从上次收到的续传
	 *THOST_TERT_QUICK:只传送登陆后公共流的内容
	 */

	//Step4.Subscribe the private and public stream
	trade_api->SubscribePrivateTopic(THOST_TERT_QUICK);
	trade_api->SubscribePublicTopic(THOST_TERT_QUICK);	

	

	//Step5.init the api
	trade_api->Init();
	
	sleep(2);
	//trade_api->Join();
	menu_view();
	menu(trade_api,trade_spi);
	cout<<"The version info:"<<trade_api->GetApiVersion()<<endl;
	cout<<"The trading day:"<<trade_api->GetTradingDay()<<endl;
	return 0;
}
void menu(api* session_api,spi* session_spi){
	
	key_type key;
	log_str("Please input your choice");
	cin>>key;
	switch(key){
		case '1':
			session_api->
		default:
			log_str("You input");log_str(key);
			break;
	}
}
void menu_view(){
	log_str("\tMENU\t",GREEN_STR);
	log_str("1.Show the market bulletin",GREEN_STR);
	log_str("2.Configure the strategy",GREEN_STR);
	log_str("3.Start the analysis and auto-trade",GREEN_STR);
	cout<<endl;
}
