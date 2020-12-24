#ifndef ORDER_H
#define ORDER_H
#include "common.h"

class hfts_order{

};
class order_handler{
    //insert order,requestID specify the request id which could be useful while adding the order management
    static int insert_order(CThostFtdcInputOrderField *pInputOrder, int nRequestID); 
    
};
void order_main();
void insert_order();
void parked_order();
void order_menu();

#endif