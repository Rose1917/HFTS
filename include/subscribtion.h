#ifndef SUBSCRIBTION_H
#define SUBSCRIBTION_H
#include "common.h"
#define market_buffer_size 1000
#define NEXT_INDEX(i) ((i+1-market_buffer_size)?i+1:0)
typedef char instr_str[7];
typedef unsigned int price_write_index;
typedef double future_val;
typedef struct future_elemdata{
    SADateTime* time;
    future_val value;
    future_elemdata(SADateTime* s,future_val i):time(s),value(i){}
    future_elemdata(){time=nullptr,value=0.0;}
}future_eledata;

class instrument_item{
    std::string instr_id;
    future_eledata prices[market_buffer_size];
    price_write_index i;
    unsigned int valid_c;

    public:instrument_item(char* name){
        instr_id.assign(name);
        i=0;
        valid_c=0;
    }
    void insert_element_data(future_elemdata e){
        prices[i]=e;
        i=NEXT_INDEX(i);
    }
    future_elemdata* get_prices(){
        return prices;
    }
    unsigned int get_wirte_index(){
        return i;
    }
    unsigned int get_valid_count(){
        return valid_c;
    }
};

class instrument_handler{
    public:static std::unordered_map<std::string,instrument_item*> *inst_set;

    public:
    static int insert_instru(instr_str instr_name);
    static int remove_instru(instr_str instr_name);
    static int insert_depth_instru(instr_str instr_name,future_eledata e);
    /*static int insert_multi_instru(instr_str instr_name[]);
    static int remove_multi_instru(instr_str instr_name[]);
    static std::set<instru>& get_instru_set();
    */
};
#endif