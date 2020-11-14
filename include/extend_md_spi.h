#ifndef EXTEND_MD_SPI
#define EXTEND_MD_SPI
#include "common.h"
class extend_md_spi :public CThostFtdcMdSpi{
	CThostFtdcMdApi* tapi=NULL;

	//构造函数
	public: extend_md_spi(CThostFtdcMdApi* api);	
	//前端链接函
	void OnFrontConnected();
	//认证响应函数
	void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//登录响应函数
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);


	//Getter and Setter
	void setTapi(CThostFtdcMdApi* api){
		this->tapi=api;
	}
	CThostFtdcMdApi* getTapi(){
		return this->tapi;
	}
};
#endif
