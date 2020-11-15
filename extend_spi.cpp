#include "include/common.h"
using namespace std;
extend_spi::extend_spi(CThostFtdcTraderApi* api){
	setTapi(api);
}

//前端链接函数
void extend_spi::OnFrontConnected(){
	log_info("front connectted,now authenticating ...");

	CThostFtdcReqAuthenticateField auth_field;
	memset(&auth_field,0,sizeof(auth_field));
	strcpy(auth_field.BrokerID,"9999");
	strcpy(auth_field.UserID,"177050");
	strcpy(auth_field.AppID,"simnow_client_test");
	strcpy(auth_field.AuthCode,"0000000000000000");

	//Authenticate
	getTapi()->ReqAuthenticate(&auth_field,0);

}
//认证结果回调函数
void extend_spi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *rsp_auth_field, CThostFtdcRspInfoField *error_info, int nRequestID, bool bIsLast) {
	#ifdef DEBUG
	log_info("Authenticate Response:");
	log_str("BrokerID:",rsp_auth_field->BrokerID);
	log_str("UserID:",rsp_auth_field->UserID);
	log_str("AppID:",rsp_auth_field->AppID);

	log_str("AppType:");log_str(rsp_auth_field->AppType);
	log_str("ErrorID");log_str(error_info->ErrorID);
	log_str("ErrorMsg",error_info->ErrorMsg);	
	#endif
	if(!error_info->ErrorID){
		log_info("Authentication Success.");
		log_info("Now Signing in...");
		CThostFtdcReqUserLoginField login_field;
		strcpy(login_field.BrokerID,rsp_auth_field->BrokerID);
		strcpy(login_field.UserID,rsp_auth_field->UserID);
		strcpy(login_field.Password,"3650599367aA");
		//to-do
		this->getTapi()->ReqUserLogin(&login_field,0);
	}
}
//登录结果函数
void extend_spi::OnRspUserLogin(CThostFtdcRspUserLoginField *rsp_login_field, CThostFtdcRspInfoField *error_info, int nRequestID, bool bIsLast){
	#ifdef DEBUG
	log_info("Login Response:");
	log_str("Trading Day:",rsp_login_field->TradingDay);
	log_str("SessionID:");log_str(rsp_login_field->SessionID);
	log_str("ErrorID");log_str(error_info->ErrorID);
	log_str("ErrorMsg",error_info->ErrorMsg);	
	#endif
	if(!error_info->ErrorID){
		log_info("Login Success");
	}
}
