#ifndef MAIN_H
#define MAIN_H
#include "common.h"
typedef CThostFtdcTraderApi api;
typedef CThostFtdcTraderSpi spi;
typedef CThostFtdcMdApi md_api;
typedef CThostFtdcMdSpi md_spi;
typedef char key_type;
void menu();
void init();
void register_front();
void menu_view();

//Configuration
std::string td_front_addr_str=std::string("tcp://180.168.146.187:10101");
char* td_front_addr=(char*) td_front_addr_str.data();
std::string md_front_addr_str=std::string("tcp://180.168.146.187:10131");
char* md_front_addr=(char*) md_front_addr_str.data();

//Global variables
api* trade_api=nullptr;
md_api* market_api=nullptr;
#endif