#include "include/common.h"
void Error::parse_error(ERROR_TYPE t){
    switch (t) {
        case INTERNET_NOT_ALIVE:
            log_error("Internet not alive,please check your internet connection");
            break;
        default:
            log_error("Unknown error has occured.");
            break;
    }
}
