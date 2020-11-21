#include "include/common.h"
using namespace std;
extern api* trade_api;
extern md_api* market_api;
void order_main(){
    place_order();
}
void place_order(){
    CThostFtdcInputOrderField order_info;
    char buffer[100];
    strcpy(order_info.BrokerID,"9999");
    strcpy(order_info.ExchangeID,"SHFE");
    strcpy(order_info.UserID,"177050");
    strcpy(order_info.InvestorID,"177050");
    
    log_str("Please input the instrument ID:");
    cin>>buffer;
    strcpy(order_info.InstrumentID,buffer);

    key_type key;
    log_str("Please choose the exchange direction:");
    log_str("1.Buy");
    log_str("2.Sell");
    cin>>key;
    if(key=='1')order_info.Direction=THOST_FTDC_D_Buy;
    else order_info.Direction=THOST_FTDC_D_Sell;

    int volume;
    log_str("Please input the volume total:");
    cin>>volume;
    order_info.VolumeTotalOriginal=volume;

    //Some default option
    order_info.LimitPrice=3200;
    order_info.OrderPriceType=THOST_FTDC_OPT_LimitPrice;
    order_info.ContingentCondition=THOST_FTDC_CC_Immediately;
    order_info.TimeCondition=THOST_FTDC_TC_GFD;
    order_info.VolumeTotalOriginal=THOST_FTDC_VC_AV;
    strcpy(order_info.CombHedgeFlag,"1");
    strcpy(order_info.CombOffsetFlag,"0");
    strcpy(order_info.GTDDate,"");
    strcpy(order_info.OrderRef,"1");
    order_info.MinVolume=0;
    order_info.ForceCloseReason=THOST_FTDC_FCC_NotForceClose;
    order_info.IsAutoSuspend=0;

    trade_api->ReqOrderInsert(&order_info,0);

    log_str("Req order insert end");
}
