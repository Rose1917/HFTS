#include "include/common.h"
using namespace std;
std::unordered_map<std::string,instrument_item*>* instrument_handler::inst_set=new std::unordered_map<std::string,instrument_item*>();
int instrument_handler::insert_instru(instr_str name){
    instrument_item* p=new instrument_item(name);
    string ts(name);
    cout<<instrument_handler::inst_set->empty();
    
}