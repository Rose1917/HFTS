#include "include/trade_handler.h"
extern InitWindow* init_window;
extern api* trade_api;

//init
unsigned int trade_handler::request_id=0;
switch_type trade_handler::trade_switch=false;
index_strategy* trade_handler::strategy=new index_strategy();
std::set<instrument_to_be_listened*>* trade_handler::instr_set=new std::set<instrument_to_be_listened*>();
std::set<instrument_to_be_listened*>* trade_handler::shangzheng_ins=new std::set<instrument_to_be_listened*>();
std::set<instrument_to_be_listened*>* trade_handler::zhongzheng_ins=new std::set<instrument_to_be_listened*>();
std::set<instrument_to_be_listened*>* trade_handler::hushen_ins=new std::set<instrument_to_be_listened*>();
QMap<QString,instrument_to_be_listened*>* trade_handler::hash_map=new QMap<QString,instrument_to_be_listened*>();

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

void trade_handler::add_instrument(QString q){
    instrument_to_be_listened* tp=new instrument_to_be_listened(q);
    parse_instr(q.toStdString(),tp->type,tp->gap_month);

    tp->model_tp=instrument_handler::get_instrument_by_id(q.toStdString());

    //set the instrument model
    trade_handler::instr_set->insert(tp);
    trade_handler::hash_map->insert(q,tp);
    switch(tp->type){
        case SHANGZHENG_50:trade_handler::shangzheng_ins->insert(tp);
        break;
        case ZHONGZHENG_500:trade_handler::zhongzheng_ins->insert(tp);
        break;
        case HUSHEN_300:trade_handler::hushen_ins->insert(tp);
        break;
        default:
        log_error("datapage::on_addtostrategy_clicked:should not reach here");
    }
    log_error("trade_handler::add_instrument");

    std::cout<<"instr_set size: "<<instr_set->size()<<" "<<std::endl;
    std::cout<<"shangzheng50 size: "<<shangzheng_ins->size()<<" "<<std::endl;
    std::cout<<"zhongzheng_ins size: "<<zhongzheng_ins->size()<<" "<<std::endl;
    std::cout<<"hushen_ins size: "<<hushen_ins->size()<<" "<<std::endl;
}
void trade_handler::remove_instrument(QString q){
    instrument_to_be_listened* tp=hash_map->value(q);
    instr_set->erase(tp);

    shangzheng_ins->erase(tp);
    zhongzheng_ins->erase(tp);
    hushen_ins->erase(tp);

    free(tp);
    log_error("trade_handler::remove_instrument");

    std::cout<<"instr_set size: "<<instr_set->size()<<" "<<std::endl;
    std::cout<<"shangzheng50 size: "<<shangzheng_ins->size()<<" "<<std::endl;
    std::cout<<"zhongzheng_ins size: "<<zhongzheng_ins->size()<<" "<<std::endl;
    std::cout<<"hushen_ins size: "<<hushen_ins->size()<<" "<<std::endl;
}
void trade_handler::make_decision(index_t t,index_val val){
    log_error("trade_handler::make decision():start up");
    if(!trade_switch)return ;

    log_error("trade_handler::make decision():point 1");
    std::set<instrument_to_be_listened*>* target_ins_set;
    switch (t) {
        case SHANGZHENG_50:target_ins_set=shangzheng_ins;
        break;
        case ZHONGZHENG_500:target_ins_set=zhongzheng_ins;
        break;
        case HUSHEN_300:target_ins_set=hushen_ins;
        break;
        default:log_error("trade_handler::make_decision:should not reach here");
        break;
    }
    log_error("trade_handler::make decision():point 2");

    ACTION_TYPE action;
    QPlainTextEdit* record = init_window->_tradingpage->get_recordtext();
    for(auto& i:*target_ins_set){
        log_error("trade_handler::make decision():point 3");
        action=strategy->decision(i->model_tp->get_last_val(),val,i->gap_month);


        //record->appendPlainText("instrument id:"+i->instrment_id);
        std::cout<<"instrument id:"<<i->instrment_id.toStdString()<<std::endl;

        char action_flag;
        if(action==BUY){
            std::cout<<"Action Buy"<<std::endl;
            action_flag=THOST_FTDC_D_Buy;
        }
        else if(action==SELL){
            std::cout<<"Action Sell"<<std::endl;
            action_flag=THOST_FTDC_D_Sell;
        }
        else{
            continue;
        }
        execute_trade(i->instrment_id.toStdString(),action_flag,i->model_tp->get_last_val());
        //record->appendPlainText("--------------------------------------------------");
    }
}
void trade_handler::execute_trade(std::string instr_id,char direction,index_val price){
    CThostFtdcInputOrderField orderfield ={0};
    strcpy(orderfield.BrokerID, "9999");
    strcpy(orderfield.InvestorID, "177050");
    strcpy(orderfield.ExchangeID, env_config::local_exchange_id[ZHONGJINSUO]);
    strcpy(orderfield.InstrumentID, instr_id.data());
    orderfield.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
    orderfield.Direction = direction;
    orderfield.LimitPrice = price;
    orderfield.VolumeTotalOriginal = 1;
    orderfield.ContingentCondition = THOST_FTDC_CC_Immediately;
    orderfield.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
    orderfield.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;

    sprintf(orderfield.OrderRef,"%d",request_id);
    request_id++;

    //Execute the command,if the trade is not set,cancel it.
    orderfield.TimeCondition = THOST_FTDC_TC_IOC;
    orderfield.VolumeCondition = THOST_FTDC_VC_CV;
    orderfield.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    int ret = trade_api->ReqOrderInsert(&orderfield, 0);

    init_window->addorder_request(QString::number(request_id),QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss"),u8"待确认");
    log_str("Req order insert end");
}

