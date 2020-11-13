#include "include/common.h"
#include <iostream>
using namespace std;
typedef CThostFtdcTraderApi api;
typedef CThostFtdcTraderSpi spi;
int main(){
#ifdef DEBUG
	cout<<"now in the debug mode"<<endl;
#endif
	//Step1.Get a trade api instance
	api* trade_api=api::CreateFtdcTraderApi("./info/");
	
	
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
	trade_api->RegisterFront("tcp://180.168.146.187:10101");
	
#ifdef DEBUG
	cout<<"OnCreateFront Function Test:"<<endl;
	trade_spi->OnFrontConnected();
#endif
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

	trade_api->Join();
	//login
	/*
	CThostFtdcReqUserLoginField login_field;
	strcpy(login_field.BrokerID,"9999");
	strcpy(login_field.UserID,"177050");
	strcpy(login_field.Password,"3650599367aA");
	trade_api->ReqUserLogin(&login_field,0);
	*/

	cout<<"The version info:"<<trade_api->GetApiVersion()<<endl;
	cout<<"The trading day:"<<trade_api->GetTradingDay()<<endl;
	return 0;
}
