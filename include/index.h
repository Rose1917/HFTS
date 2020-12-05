#ifndef INDEX_H
#define INDEX_H
#include "common.h"
enum index_t{
    SHANGZHENG_50,ZHONGZHENG_500,HUSHEN_300
};
typedef double index_val;
class share_index{
    index_t type;
    index_val value;
    const char* post_para[]={"000016","000905","000300"};
    public:
    share_index(index_t t,index_val v=0){
        this->type=t;this->value=v;
    }

    int update_val();
    void set_index_type(index_t t){this->type=t;}
    void set_index_val(index_val val){
        this->value=val;
    }
    index_t get_index_type(){return this->type;}
    index_val get_index_val(){return this->value;}

};
#endif