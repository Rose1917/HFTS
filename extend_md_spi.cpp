#include "include/common.h"
using namespace std;
extend_md_spi::extend_md_spi(CThostFtdcMdApi* api){
	setTapi(api);
}

//前端链接函数
void extend_md_spi::OnFrontConnected(){
	log_info("Market front connectted,now logging in...");

}
//认证结果回调函数
void extend_md_spi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *rsp_auth_field, CThostFtdcRspInfoField *error_info, int nRequestID, bool bIsLast) {
	
}
//登录结果函数
void extend_md_spi::OnRspUserLogin(CThostFtdcRspUserLoginField *rsp_login_field, CThostFtdcRspInfoField *error_info, int nRequestID, bool bIsLast){
	
}
