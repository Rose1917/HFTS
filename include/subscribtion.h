#ifndef SUBSCRIBTION_H
#define SUBSCRIBTION_H
#include "common.h"
#define market_buffer_size 10
#define NEXT_INDEX(i) ((i+1-market_buffer_size)?i+1:0)
#define COUNT_PLUS(i) ((market_buffer_size-i)?i+1:i)
typedef char instr_str[7];
typedef unsigned int price_write_index;
typedef double future_val;
typedef struct future_elemdata{
    SADateTime time;
    future_val value;
    future_elemdata(SADateTime &s,future_val i):time(s),value(i){}
    future_elemdata(){time=SADateTime(),value=0.0;}
}future_eledata;

class instrument_item{
    std::string instr_id;
    future_eledata* prices[market_buffer_size];
    price_write_index i;
    unsigned int valid_c;

    public:instrument_item(char* name){
        instr_id.assign(name);
        i=0;
        valid_c=0;
    }
    void insert_element_data(future_elemdata* e){
        prices[i]=e;
        i=NEXT_INDEX(i);
        valid_c=COUNT_PLUS(valid_c);
    }
    future_elemdata** get_prices(){
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
    static int insert_depth_instru(instr_str instr_name,future_eledata* e);
    
    //@Description:if found return the address of object,else return nullptr
    //@Param:the instrument id
    static instrument_item* get_instrument_by_id(instr_str name);

    /*static int insert_multi_instru(instr_str instr_name[]);
    static int remove_multi_instru(instr_str instr_name[]);
    static std::set<instru>& get_instru_set();
    */
};
#endif