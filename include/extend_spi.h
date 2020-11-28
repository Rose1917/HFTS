#ifndef EXTEND_SPI
#define EXTEND_SPI
#include "common.h"
class extend_spi :public CThostFtdcTraderSpi{
	CThostFtdcTraderApi* tapi=NULL;

	//构造函数
	public: extend_spi(CThostFtdcTraderApi* api);
	//登录请求相应函数
	void OnRspUserLogin(CThostFtdcRspUserLoginField*,CThostFtdcRspInfoField *,int,bool);	
	//前端链接函
	void OnFrontConnected();
	//认证响应函数
	void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//用户信息函数
	void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//用户信息确认函数
	void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//收到订单
	void OnRtnOrder(CThostFtdcOrderField *pOrder);
	//报单结果信息
	void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//parked order
	void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//Getter and Setter
	void setTapi(CThostFtdcTraderApi* api){
		this->tapi=api;
	}
	CThostFtdcTraderApi* getTapi(){
		return this->tapi;
	}
};
#endif
