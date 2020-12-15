#ifndef STATUS_H
#define STATUS_H
enum status_code{
    MARKET_FRONT,TRADER_FRONT,MARKET_LOGIN,TRADER_LOGIN
};
class system_status{
    public:
    static bool is_market_connected;
    static bool is_trader_connected;
    static bool is_market_logined;
    static bool is_trader_logined;

    static void wait_code_till_true(status_code c){
        switch(c){
            case MARKET_FRONT:
                while(true)if(!is_market_connected)continue;else break;
                break;
            case TRADER_FRONT:
                while(true)if(!is_trader_connected)continue;else break;
                break;
            case MARKET_LOGIN:
                while(true)if(!is_market_logined)continue;else break;
                break;
            case TRADER_LOGIN:
                while(true)if(!is_trader_logined)continue;else break;
                break;
        }
    }
};
#endif