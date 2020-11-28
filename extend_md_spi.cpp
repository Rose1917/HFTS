#include "include/common.h"
#define PRICE_MAX_LEN 20
using namespace std;
char* subID[]={"ag2012","hc2101","zn2011","sn2011","ag2110","ag2111"};
bool show_flag=false;

extend_md_spi::extend_md_spi(CThostFtdcMdApi* api){
	setTapi(api);
}

//前端链接函数
void extend_md_spi::OnFrontConnected(){
	log_info("Market front connectted,now logging in...");
	CThostFtdcReqUserLoginField login_field;
	strcpy(login_field.BrokerID,"9999");
	strcpy(login_field.UserID,"177050");
	strcpy(login_field.Password,"3650599367aA");
	//to-do
	this->getTapi()->ReqUserLogin(&login_field,0);
}

//登录结果函数
void extend_md_spi::OnRspUserLogin(CThostFtdcRspUserLoginField *rsp_login_field, CThostFtdcRspInfoField *error_info, int nRequestID, bool bIsLast){
	#ifdef DEBUG
	log_info("Market login response:");
	log_str("SessionID:");log_str(rsp_login_field->SessionID);
	log_str("System Name:");log_str(rsp_login_field->SystemName);
	log_str("Login Time:");log_str(rsp_login_field->LoginTime);
	log_str("Trading Day:",rsp_login_field->TradingDay);
	log_str("User ID:");log_str(rsp_login_field->UserID);
	log_str("ErrorID:");log_str(error_info->ErrorID);
	log_str("ErrorMsg:",error_info->ErrorMsg);	
	#endif
	if(!error_info->ErrorID){
		std::cout << "=====Login Success=====" << std::endl;
		std::cout << "Trading Day： " << rsp_login_field->TradingDay << std::endl;
		std::cout << "Login Time： " << rsp_login_field->LoginTime << std::endl;
		std::cout << "Broker ID： " << rsp_login_field->BrokerID << std::endl;
		std::cout << "User Account： " << rsp_login_field->UserID << std::endl;
		this->getTapi()->SubscribeMarketData(subID,sizeof(subID)/sizeof(char*));
	}
}
void extend_md_spi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	#ifdef DEBUG
	log_info("Subscribtion responce:");
	log_str("InstrumentID=");log_str(pSpecificInstrument->InstrumentID);
	log_str("ErrorID:");log_str(pRspInfo->ErrorID);
	log_str("Error Message:",pRspInfo->ErrorMsg);
	#endif
	if(!pRspInfo->ErrorID)
	{
		log_str("InstrumentID=",pSpecificInstrument->InstrumentID);
		log_str("Subscribtion success.");
	}
	else{
		cout<<"Error ID"<<" "<<pRspInfo->ErrorID;
		log_str("Error message:",pRspInfo->ErrorMsg);
	}
}
//数据接收函数
void extend_md_spi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *data){
	if(!show_flag)return ;
	
	log_error("Market info received");

	/*
	log_str("ExchangeID:",data->ExchangeID,GREEN_STR,1);
	log_str("Exchange Instance ID:",data->ExchangeInstID,GREEN_STR,1);
	*/
	log_str("Instrument ID:",data->InstrumentID,GREEN_STR,1);
	log_str("Trading day:",data->TradingDay,GREEN_STR,1);
	log_str("Action day:",data->ActionDay,GREEN_STR,1);
	log_str("Last Price:",double2c(data->LastPrice),GREEN_STR,1);
	log_str("Ask Price:",double2c(data->AskPrice1),GREEN_STR,1);
	log_str("Bid Price:",double2c(data->BidPrice1),GREEN_STR,1);
	
	//log_str("")
	//data->TradingDay
	


	
	//printf("%f\n",data->LastPrice);
	
	
}

