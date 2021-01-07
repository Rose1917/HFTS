#ifndef MAIN_H
#define MAIN_H
#include "common.h"
typedef CThostFtdcTraderApi api;
typedef CThostFtdcTraderSpi spi;
typedef CThostFtdcMdApi md_api;
typedef CThostFtdcMdSpi md_spi;
typedef CThostFtdcTraderApi* api_ptr;
typedef CThostFtdcTraderSpi* spi_ptr;
typedef CThostFtdcMdApi* md_api_ptr;
typedef CThostFtdcMdSpi* md_spi_ptr;
typedef char key_type;


void menu();
int market_init();
int trader_init();
int login_market(char*,char*);
int subsribe_market_data(char*);
int general_init();
void main_init();

int req_authenticate(std::string broker_id=nullptr,std::string user_id=nullptr,std::string app_id=nullptr,std::string authen_code=nullptr);
int login_trader(std::string user_name=nullptr,std::string pwd=nullptr);

void menu_view();
void print_version();
void print_prompt();
void load_doc(char*);
#endif
