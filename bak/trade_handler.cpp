#include "include/trade_handler.h"
//init
switch_type trade_handler::trade_switch=false;
index_strategy* trade_handler::strategy=new index_strategy();
std::set<instrument_to_be_listened*>* trade_handler::instr_set=new std::set<instrument_to_be_listened*>();
std::set<instrument_to_be_listened*>* trade_handler::shangzheng_ins=new std::set<instrument_to_be_listened*>();
std::set<instrument_to_be_listened*>* trade_handler::zhongzheng_ins=new std::set<instrument_to_be_listened*>();
std::set<instrument_to_be_listened*>* trade_handler::hushen_ins=new std::set<instrument_to_be_listened*>();

/*
void trade_handler::parse_instr(std::string s,index_t & t,unsigned & gap){
    switch (s[1]) {
        case 'H':
            t=SHANGZHENG_50;break;
        case 'C':
            t=ZHONGZHENG_500;break;
        case 'F':
            t=HUSHEN_300;break;
        default:
            log_error("trade_handler::parse_instr:should not reach here");
    }
    gap=s[5]-'1';
}
void trade_handler::make_decision(std::string instr_name,index_val ins_val){
    instrument_to_be_listened* temp_ins=new instrument_to_be_listened();
    trade_handler::parse_instr(instr_name,temp_ins->type,temp_ins->gap_month);
}

void trade_handler::add_instrument(QString s){
    instrument_to_be_listened* tp=new instrument_to_be_listened(s);
   // parse_instr(s.toStdString(),tp->type,tp->gap_month);

    log_error("trade_handler::add_instrument");
    std::cout<<"instrument id: "<<s.toStdString()<<std::endl;
    std::cout<<"the instrument type: "<<tp->type<<std::endl;
    std::cout<<"gap month: "<<tp->gap_month<<std::endl;

    /*
    //set the instrument model
    instrument_to_be_listened* temp_ins=new instrument_to_be_listened();
    trade_handler::parse_instr(s->getname().toStdString(),temp_ins->type,temp_ins->gap_month);

    trade_handler::instr_set->insert(temp_ins);
    switch(temp_ins->type){
        case SHANGZHENG_50:trade_handler::shangzheng_ins->insert(temp_ins);
        break;
    case ZHONGZHENG_500:trade_handler::zhongzheng_ins->insert(temp_ins);
        break;
     case HUSHEN_300:trade_handler::hushen_ins->insert(temp_ins);
        break;
    default:
        log_error("datapage::on_addtostrategy_clicked:should not reach here");
    }

}
*/
