#include "include/common.h"
using namespace std;
extend_spi::extend_spi(CThostFtdcTraderApi* api){
	setTapi(api);
}

//前端链接函数
void extend_spi::OnFrontConnected(){
	log_info("trader front connectted,now authenticating ...");
	system_status::is_trader_connected=true;
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
		system_status::is_authen_success=true;
		log_info("Authentication Success.");
		log_info("Now Signing in...");
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
		system_status::is_trader_logined=true;
		log_info("Login Success");
		CThostFtdcQrySettlementInfoField settle_info_field;
		strcpy(settle_info_field.BrokerID,"9999");
		strcpy(settle_info_field.InvestorID,"177050");
		strcpy(settle_info_field.TradingDay,rsp_login_field->TradingDay);
		this->getTapi()->ReqQrySettlementInfo(&settle_info_field,0);
	}
}
void extend_spi::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	log_info("OnRspQrySettlementInfo");
	if(pSettlementInfo!=NULL){
		log_str("content:");
		log_info(pSettlementInfo->Content);
	}
	else log_str("content null");

	//Send settlement confirm info
	CThostFtdcSettlementInfoConfirmField settle_confirm_field;
	strcpy(settle_confirm_field.BrokerID,"9999");
	strcpy(settle_confirm_field.InvestorID,"177050");
	this->getTapi()->ReqSettlementInfoConfirm(&settle_confirm_field,0);

}
void extend_spi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	log_info("OnRspQrySettlementInfoConfirm");
	if(!pRspInfo->ErrorID) log_str("Confirm success");
	else log_error("Error message:",pRspInfo->ErrorMsg);
}
void extend_spi::OnRtnOrder(CThostFtdcOrderField *pOrder){
	log_info("OnRtnOrder function:");
	cout<<"Order status:";log_str(pOrder->OrderStatus);
	log_str("Status message:",pOrder->StatusMsg);
}
void extend_spi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	ofstream fout("output.txt");
	log_info("OnRspOrderInsert function");
	printf("ErrorID:%d",pRspInfo->ErrorID);
	if(!pRspInfo->ErrorID) log_info("Insert request send success");
	else log_info("Error Msg:",pRspInfo->ErrorMsg);
	fout<<(pRspInfo->ErrorMsg);
}
void extend_spi::OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	ofstream fout("output.txt");
	log_info("OnRspParkedOrderInsert function");
	printf("ErrorID:%d",pRspInfo->ErrorID);
	if(!pRspInfo->ErrorID) log_info("Insert request send success");
	else log_info("Error Msg:",pRspInfo->ErrorMsg);
	fout<<(pRspInfo->ErrorMsg);
}


