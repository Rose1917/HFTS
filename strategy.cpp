#include "include/common.h"
using namespace std;
ACTION_TYPE index_strategy::decision(double future_price,double index_val){
    //Calculate the ideal price of future
    ideal_price=index_val*pow(E,(annual_interest_rate-annual_bonus_rate)*interval_month_lenth/12.0);
    cout<<"ideal price"<<ideal_price<<endl;

    //Calculate the arbitrage spread.
    arbitrage_cost=future_commission+impact_cost+index_val*stock_commision_rate+stock_stamp_duty_rate*index_val+stock_impact_cost*index_val+index_track_error_rate*index_val+cost_borrow_spread*index_val;
    arbitrage_cost*=security_factor;
    cout<<"arbitrage cost"<<arbitrage_cost<<endl;

    //Calculate the uppper and lower edge
    upper_edge=ideal_price+arbitrage_cost;
    lower_edge=ideal_price-arbitrage_cost;

    //In this case,the current future price is too high.we should go short
    if(future_price>upper_edge)
        return SELL;
    //In this case,the current future price is too low,we should go long
    if(future_price<upper_edge)
        return BUY;
    //In this case,the current future price is reasonable,we do nothing
    return NONE;
}