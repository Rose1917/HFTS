#ifndef CONFIG_H
#define CONFIG_H
#define ADDR_MAX_SIZE 100
#define PAGE_SIZE 5
#include "common.h"
//Configuration
enum market_links{
    LINK_1,LINK2,LINK3,LINK4,LINK5
};
class env_config{
     
    char* td_front_addr;
    char* md_front_addr;
    int page_size;
    
    char* db_host;
    char* db_user;
    char* db_pwd;
    char* db_name;
    
    char* investor_id;
    char* broker_id;

    public:
    static char* local_md_config[5];

    public:
    env_config(char* td="tcp://180.168.146.187:10101",char* md="tcp://180.168.146.187:10114",char* host="129.211.69.209@",char* user="root",char* pwd="Hhcl199904020",char* dbname="USE HFTS"){
        td_front_addr=(char*)malloc(sizeof(char)*ADDR_MAX_SIZE);
        md_front_addr=(char*)malloc(sizeof(char)*ADDR_MAX_SIZE);
        db_host=(char*)malloc(sizeof(char)*ADDR_MAX_SIZE);
        db_user=(char*)malloc(sizeof(char)*ADDR_MAX_SIZE);
        db_pwd=(char*)malloc(sizeof(char)*ADDR_MAX_SIZE);
        db_name=(char*)malloc(sizeof(char)*ADDR_MAX_SIZE);
        investor_id=(char*)malloc(sizeof(char)*ADDR_MAX_SIZE);
        broker_id=(char*)malloc(sizeof(char)*ADDR_MAX_SIZE);

        set_td_front_addr(td);
        set_md_front_addr(md);
        set_db_host(host);
        set_db_user(user);
        set_db_pwd(pwd);
        set_db_name(dbname);
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
    char* get_host_name(){
        return db_host;
    }
    int set_db_host(char* h){
        return strcpy(db_host,h)!=NULL;
    }
    char* get_db_user(){
        return db_user;
    }
    int set_db_user(char* u){
        return strcpy(db_user,u)!=NULL;
    }
    char* get_db_pwd(){
        return db_pwd;
    }
    int set_db_pwd(char* p){
        return strcpy(db_pwd,p)!=NULL;
    }
    int set_db_name(char* n){
        return strcpy(db_name,n)!=NULL;
    }
    char* get_db_name(){
        return db_name;
    }
    char* get_investor_id(){
        return investor_id;
    }
    int set_investor_id(const char* i){
        return strcpy(investor_id,i)!=NULL;
    }
    char* get_broker_id(){
        return broker_id;
    }
    int set_broker_id(const char* i){
        return strcpy(broker_id,i)!=NULL;
    }
    

};
typedef env_config* econf_ptr;
typedef env_config env_config;

#endif