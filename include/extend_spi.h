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
	


	//Getter and Setter
	void setTapi(CThostFtdcTraderApi* api){
		this->tapi=api;
	}
	CThostFtdcTraderApi* getTapi(){
		return this->tapi;
	}
};
#endif
