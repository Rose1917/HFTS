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

    std::list<future_eledata*>* prices;
    price_write_index i;
    unsigned int valid_c;
    future_val last_val;

    public:instrument_item(char* name){
        instr_id.assign(name);
        prices=new std::list<future_eledata*>();
        i=0;
        valid_c=0;
    }
    void insert_element_data(future_elemdata* e){
        if(prices->size()==market_buffer_size)prices->pop_front();
        prices->push_back(e);
        last_val=e->value;
    }
    std::list<future_eledata*>* get_prices(){
        return prices;
    }
    unsigned int get_wirte_index(){
        return i;
    }
    unsigned int get_valid_count(){
        return valid_c;
    }
    future_val get_last_val(){
        return last_val;
    }
    void set_last_val(future_val f){
        last_val=f;
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
    static instrument_item* get_instrument_by_id(std::string name);

    /*static int insert_multi_instru(instr_str instr_name[]);
    static int remove_multi_instru(instr_str instr_name[]);
    static std::set<instru>& get_instru_set();
    */
};
#endif
