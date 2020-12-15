#include "include/common.h"
#define PRICE_MAX_LEN 20
using namespace std;
char* subID[]={"IF2012","IF2101","IF2103","IH2012","IH2101","IH2103","IC2012","IC2101","IC2103","IC2106"};
bool show_flag=true;
bool front_connected=false;
//,"zn2011","sn2011","ag2110","ag2111"
extend_md_spi::extend_md_spi(CThostFtdcMdApi* api){
	setTapi(api);
}

//前端链接函数
void extend_md_spi::OnFrontConnected(){
	log_info("Market front connectted,now logging in...");
	system_status::is_market_connected=true;
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
		system_status::is_market_logined=true;
		log_info("====Market Login Successs====");
	}
}
//Once the contract is subscribed succesfully.it will touch a new table if it does not exist.
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
		hfts_db::create_contract(pSpecificInstrument->InstrumentID);
		log_str("Subscribtion success.");
	}
	else{
		cout<<"Error ID"<<" "<<pRspInfo->ErrorID;
		log_str("Error message:",pRspInfo->ErrorMsg);
	}
}
//Depth data collection function.
//Once it receive a message,it will be called.

void extend_md_spi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *data){
	if(!show_flag)return ;
	
	//log_error("Market info received");
	hfts_db::insert_depth_db(data);
	/*
	log_str("ExchangeID:",data->ExchangeID,GREEN_STR,1);
	log_str("Exchange Instance ID:",data->ExchangeInstID,GREEN_STR,1);
	*/
	
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
	
	//log_str("")
	//data->TradingDay
	


	
	//printf("%f\n",data->LastPrice);
	
	
}

