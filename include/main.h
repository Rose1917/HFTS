#ifndef MAIN_H
#define MAIN_H
#include "common.h"
typedef CThostFtdcTraderApi api;
typedef CThostFtdcTraderSpi spi;
typedef CThostFtdcMdApi md_api;
typedef CThostFtdcMdSpi md_spi;
typedef char key_type;
void menu(api* ,spi*,md_api*,md_spi*);

//show the simple console menu
void menu_view();
#endif