#ifndef TRADE_HANDLER_H
#define TRADE_HANDLER_H
#include "common.h"
#include <QMap>
typedef bool switch_type;
struct instrument_to_be_listened{
    index_t type;
    unsigned gap_month;
    QString instrment_id;
    class instrument_item* model_tp;

    instrument_to_be_listened(index_t t,unsigned g,QString s):type(t),gap_month(g),instrment_id(s){}
    instrument_to_be_listened(QString s):instrment_id(s){}
    instrument_to_be_listened(index_t t,unsigned g):type(t),gap_month(g){}
    instrument_to_be_listened(){}
};

class trade_handler{
public:
    static switch_type trade_switch;
    static index_strategy* strategy;
    static unsigned int request_id;

    static std::set<instrument_to_be_listened*> *instr_set;
    static std::set<instrument_to_be_listened*> *shangzheng_ins;
    static std::set<instrument_to_be_listened*> *zhongzheng_ins;
    static std::set<instrument_to_be_listened*> *hushen_ins;

    static QMap<QString,instrument_to_be_listened*>* hash_map;

    static void add_instrument(QString );
    static void remove_instrument(QString);
    static void make_decision(index_t t,index_val v);
    static void parse_instr(std::string,index_t &,unsigned &);
    static void execute_trade(std::string instr_id,char direction,index_val price);

};


#endif // TRADE_HANDLER_H
