#ifndef STRATEGY_H
#define STRATEGY_H
enum ACTION_TYPE{
    BUY,SELL,NONE
};
class index_strategy{
    //The following data to calculate the current ideal price of future
    double annual_interest_rate;
    double annual_bonus_rate;
    int interval_month_lenth;

    //The following data to calculate the edges
    double future_commission;
    double impact_cost;
    double stock_commision_rate;
    double stock_stamp_duty_rate;
    double stock_impact_cost;
    double index_track_error_rate;
    double cost_borrow_spread;

    //The security factor
    double security_factor;



    //Intermediate vars
    double upper_edge = 0.0;
    double lower_edge = 0.0;
    double ideal_price = 0.0;


//Constructor init the default data
index_strategy(){
    annual_interest_rate = 0.05;
    annual_bonus_rate = 0.03;
    interval_month_lenth = 0;

    security_factor=1.0;

    future_commission = 0.2;
    impact_cost = 0.2;
    stock_commision_rate = 0.04;
    stock_stamp_duty_rate = 0.01;
    stock_impact_cost = 0.005;
    index_track_error_rate = 0.02;
    cost_borrow_spread = 0.03;
}
ACTION_TYPE desion(double future_price,double index_val){
    
}



public:
    double getAnnual_interest_rate()
    {
        return this.annual_interest_rate;
    }

public:
    void setAnnual_interest_rate(double annual_interest_rate)
    {
        this.annual_interest_rate = annual_interest_rate;
    }

public:
    double getAnnual_bonus_rate()
    {
        return this.annual_bonus_rate;
    }

public:
    void setAnnual_bonus_rate(double annual_bonus_rate)
    {
        this.annual_bonus_rate = annual_bonus_rate;
    }

public:
    int getInterval_month_lenth()
    {
        return this.interval_month_lenth;
    }

public:
    void setInterval_month_lenth(int interval_month_lenth)
    {
        this.interval_month_lenth = interval_month_lenth;
    }

public:
    double getFuture_commission()
    {
        return this.future_commission;
    }

public:
    void setFuture_commission(double future_commission)
    {
        this.future_commission = future_commission;
    }

public:
    double getImpact_cost()
    {
        return this.impact_cost;
    }

public:
    void setImpact_cost(double impact_cost)
    {
        this.impact_cost = impact_cost;
    }

public:
    double getstock_commision_rate()
    {
        return this.stock_commision_rate;
    }

public:
    void setstock_commision_rate(double stock_commision_rate)
    {
        this.stock_commision_rate = stock_commision_rate;
    }

public:
    double getStock_stamp_duty_rate()
    {
        return this.stock_stamp_duty_rate;
    }

public:
    void setStock_stamp_duty_rate(double stock_stamp_duty_rate)
    {
        this.stock_stamp_duty_rate = stock_stamp_duty_rate;
    }

public:
    double getStock_impact_cost()
    {
        return this.stock_impact_cost;
    }

public:
    void setStock_impact_cost(double stock_impact_cost)
    {
        this.stock_impact_cost = stock_impact_cost;
    }

public:
    double getIndex_track_error_rate()
    {
        return this.index_track_error_rate;
    }

public:
    void setIndex_track_error_rate(double index_track_error_rate)
    {
        this.index_track_error_rate = index_track_error_rate;
    }

public:
    double getCost_borrow_spread()
    {
        return this.cost_borrow_spread;
    }

public:
    void setCost_borrow_spread(double cost_borrow_spread)
    {
        this.cost_borrow_spread = cost_borrow_spread;
    }
public:
    double getSecurity_factor()
    {
        return this.security_factor;
    }

public:
    void setSecurity_factor(double security_factor)
    {
        this.security_factor = security_factor;
    }
}
#endif