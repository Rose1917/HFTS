#ifndef EXTEND_MD_SPI
#define EXTEND_MD_SPI
#include "common.h"
class extend_md_spi :public CThostFtdcMdSpi{
	CThostFtdcMdApi* tapi=NULL;

	//构造函数
	public: extend_md_spi(CThostFtdcMdApi* api);	
	//前端链接函
	void OnFrontConnected();
	//登录响应函数
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//订阅响应函数
	void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//订阅信息获取
	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
	//取消订阅响应函数
	void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	
	//Getter and Setter
	void setTapi(CThostFtdcMdApi* api){
		this->tapi=api;
	}
	CThostFtdcMdApi* getTapi(){
		return this->tapi;
	}
};
#endif
