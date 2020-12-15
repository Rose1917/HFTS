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
void menu_view();
void print_version();
void print_prompt();
void load_doc(char*);
#endif