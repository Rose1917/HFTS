#include "include/common.h"
using namespace std;
extern api* trade_api;
extern md_api* market_api;
std::unordered_map<std::string,instrument_item*>* instrument_handler::inst_set=new std::unordered_map<std::string,instrument_item*>();
int instrument_handler::insert_instru(instr_str name){
    
    //the instrument already exists
    if(instrument_handler::inst_set->count(string(name))){
        #ifdef DEBUG
        log_info("INSERT_INSTRU:already exists");
        #endif
        return 0;
    }
    //subscribe directly
    system_status::is_subscribed=false;
    market_api->SubscribeMarketData(&name,1);
    
    //wait the result
    if((system_status::wait_code_till_true(SUBSCRIBE)))
    return -1;
    
    //insert to the handler
    instrument_item* p=new instrument_item(name);
    (*(instrument_handler::inst_set))[string(name)]=p;
    return 0;
}
int instrument_handler::remove_instru(instr_str name){
    //try to earse from the handler directly
    int erase_size=instrument_handler::inst_set->erase(string(name));
    if(!erase_size){
        #ifdef DEBUG
        log_info("REMOVE_INSTR:NONE OF THE INSTRUMENT",name);
        #endif
        return 0;
    }

    system_status::is_unsubscribed=false;
    market_api->UnSubscribeMarketData(&name,1);
    if(system_status::wait_code_till_true(UNSUBSCRIBE)){
        return -1;
    }
}
int instrument_handler::insert_depth_instru(instr_str name,future_eledata* e){
    instrument_item* p;
    
    //Got the memory object
    if(instrument_handler::inst_set->find(string(name))==instrument_handler::inst_set->end()){
        log_error("INSERT DEPTH DATA:THE TARGET OBJECT NOT FOUND");
        return 0;
    }else p=instrument_handler::inst_set->find(string(name))->second;

    //Put the data into the object
    p->insert_element_data(e);
    return 0;
}
instrument_item* instrument_handler::get_instrument_by_id(instr_str name){
    instrument_item* p;
    
    if(instrument_handler::inst_set->find(string(name))==instrument_handler::inst_set->end()){
        log_error("INSERT DEPTH DATA:THE TARGET OBJECT NOT FOUND");
        return nullptr;
    }else p=instrument_handler::inst_set->find(string(name))->second;

    return p;
}