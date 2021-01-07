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
	
	//收到订单，这个函数会被回调：CTP风控通过之后、交易所风控通过之后、交易通过之后被调用

	void OnRtnOrder(CThostFtdcOrderField *pOrder);
	//交易成功
	void OnRtnTrade(CThostFtdcTradeField *pTrade);
	
	//保单错误信息
	void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);
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
