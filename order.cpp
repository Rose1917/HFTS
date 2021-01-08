#include "include/common.h"
using namespace std;
extern api* trade_api;
extern md_api* market_api;
extern econf_ptr econf;
void order_main(){
    key_type key;
    order_menu();
    while(true){
        cin>>key;
        switch(key){
            case '1':
                parked_order();break;
            case '5':
                insert_order();break;
            case '0':
                return ;
            default:
                return ;
        }
    }
    insert_order();
}
void parked_order(){
    CThostFtdcParkedOrderField order_info;
    strcpy(order_info.BrokerID,"9999");
	
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
    order_info.OrderPriceType=THOST_FTDC_OPT_LimitPrice;
    order_info.LimitPrice=6000;

    order_info.ContingentCondition=THOST_FTDC_CC_Immediately;
    order_info.TimeCondition=THOST_FTDC_TC_GFD;
    order_info.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
    order_info.CombHedgeFlag[0] = THOST_FTDC_HF_Hedge;
    
    strcpy(order_info.OrderRef,"1");
    order_info.MinVolume=1;
    order_info.ForceCloseReason=THOST_FTDC_FCC_NotForceClose;
    order_info.IsAutoSuspend=0;
    trade_api->ReqParkedOrderInsert(&order_info,0);

    log_str("Req order insert end");
}
void insert_order(){
    //FOK

}
void order_menu(){
    log_str("\tMENU\t",GREEN_STR);
	log_str("1.Place a parked order",GREEN_STR);
	log_str("2.Action an order ",GREEN_STR);
	log_str("3.Remove a parked order",GREEN_STR);
	log_str("4.Remove a action order",GREEN_STR);
	log_str("5.Insert an order",GREEN_STR);
	log_str("6.Action an order",GREEN_STR);
	log_str("0.exit",GREEN_STR);
    cout<<":";
}

int order_handler::insert_order(CThostFtdcInputOrderField *pInputOrder, int nRequestID){
    
    return trade_api->ReqOrderInsert(pInputOrder,nRequestID);
}
