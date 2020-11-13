#include "include/common.h"
using namespace std;
extend_spi::extend_spi(CThostFtdcTraderApi* api){
	setTapi(api);
}
//登录请求相应函数
void extend_spi::OnRspUserLogin(CThostFtdcRspUserLoginField*,CThostFtdcRspInfoField *,int,bool){
	cout<<"Login success"<<endl;
}
//前端链接函
void extend_spi::OnFrontConnected(){
	cout<<"Front Connected"<<endl;
}
