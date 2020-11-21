#ifndef CONFIG_H
#define CONFIG_H
#define ADDR_MAX_SIZE 100
#define PAGE_SIZE 5
#include "common.h"
//Configuration
class env_config{
    char* td_front_addr;
    char* md_front_addr;
    int page_size;

    public:
    env_config(){
        td_front_addr=(char*)malloc(sizeof(char)*ADDR_MAX_SIZE);
        md_front_addr=(char*)malloc(sizeof(char)*ADDR_MAX_SIZE);
        set_page_size(PAGE_SIZE);
    }
    env_config(char* td,char* md){
        td_front_addr=(char*)malloc(sizeof(char)*ADDR_MAX_SIZE);
        md_front_addr=(char*)malloc(sizeof(char)*ADDR_MAX_SIZE);
        set_td_front_addr(td);
        set_md_front_addr(md);
        set_page_size(PAGE_SIZE);
    }
    int set_td_front_addr(char* new_addr){
        return strcpy(td_front_addr,new_addr)!=NULL;
    }
    char* get_td_front_addr(){
        return td_front_addr;
    }
    int set_md_front_addr(char* new_addr){
        return strcpy(md_front_addr,new_addr)!=NULL;
    }
    char* get_md_front_addr(){
        return md_front_addr;
    }
    void set_page_size(int t){
        page_size=t;
    }
    int get_page_size(){
        return page_size;
    }
};
typedef env_config* econf_ptr;
typedef env_config env_config;
#endif