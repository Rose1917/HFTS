#ifndef TRADE_HANDLER_H
#define TRADE_HANDLER_H
#include "index.h"
typedef bool switch_type;
struct instrument_to_be_listened{
    index_t type;
    unsigned gap_month;
    instrument_to_be_listened(index_t t,unsigned g):type(t),gap_month(g){}
    instrument_to_be_listened(){}
};

class trade_handler{
public:
    static switch_type trade_switch;
    static index_strategy* strategy;

    static std::set<instrument_to_be_listened*> *instr_set;
    static std::set<instrument_to_be_listened*> *shangzheng_ins;
    static std::set<instrument_to_be_listened*> *zhongzheng_ins;
    static std::set<instrument_to_be_listened*> *hushen_ins;

   /*static void add_instrument(QString );
    static void make_decision(std::string instr_name,index_val ins_val);
    static void parse_instr(std::string,index_t &,unsigned &);
    */
};

#endif // TRADE_HANDLER_H
