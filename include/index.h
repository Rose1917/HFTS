#ifndef INDEX_H
#define INDEX_H
#include "common.h"
#define MEM_MAX_SIZE 500
enum index_t{
    SHANGZHENG_50,ZHONGZHENG_500,HUSHEN_300
};
typedef double index_val;
typedef struct index_eledata{
    SADateTime time;
    index_val value;
    index_eledata(SADateTime s,index_val i):time(s),value(i){}
}index_eledata;
class share_index{
    index_t type;
    index_val value;
    std::list<index_eledata> market_data;
    char* post_para[4]={"000016","000905","000300"};
    
    public:
    share_index(index_t t,index_val v=0){
        this->type=t;this->value=v;
    }

    int update_val();
    int insert_data(index_eledata e);
    void set_index_type(index_t t){this->type=t;}
    void set_index_val(index_val val){
        this->value=val;
    }
    index_t get_index_type(){return this->type;}
    index_val get_index_val(){return this->value;}

};

//communication buffer
typedef struct cm_buffer{
    bool is_updated[3];
    index_val val[3];
    SADateTime* last_tick_time[3];
    cm_buffer(){
        for(int i=0;i<3;i++){
            last_tick_time[i]=new SADateTime(0,0,0,0,0,0,(unsigned int)0);
            is_updated[i]=false;
            val[i]=0.0;
        }
    }
}cm_buffer;
#endif