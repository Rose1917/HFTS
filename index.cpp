#include "include/common.h"
#include "linechartblockview.h"
#include <curl/curl.h>
#include <pthread.h>
#define DEBUG
using namespace std;
cm_buffer index_buffer;
SADateTime last_tick_time();
extern InitWindow* init_window;
//redefine == of SADateTime
qreal share_index::shangzheng50_count=0.0;
qreal share_index::zhongzheng500_count=0.0;
qreal share_index::hushen300_count=0.0;
pthread_mutex_t mutex_x=PTHREAD_MUTEX_INITIALIZER;
bool operator ==(const SADateTime s1,const SADateTime s2){
  return (SAString)s1==(SAString)s2&&s1.Fraction()==s2.Fraction();
}



//2020-12-04,15:02:13,00
int parse_date_time(std::string str,SADateTime** s){
    int year,month,day,hour,minute,second,fraction;
    //year
    sscanf(str.substr(0,4).data(),"%d",&year);
    sscanf(str.substr(5,2).data(),"%d",&month);
    sscanf(str.substr(8,2).data(),"%d",&day);
    sscanf(str.substr(11,2).data(),"%d",&hour);
    sscanf(str.substr(14,2).data(),"%d",&minute);
    sscanf(str.substr(17,2).data(),"%d",&second);
    sscanf(str.substr(20,2).data(),"%d",&fraction);
    fraction*=1000000;
    #ifdef DEBUG
    cout<<"update time parsed data:"<<year<<month<<day<<hour<<minute<<second<<fraction<<endl;
    #endif
    *s=new SADateTime(year,month,day,hour,minute,second,fraction);
    return 0;
}

//Parse the index type by identifying the character of the source string
index_t parse_index_type(const char* s){
    if(s[16]=='0')return SHANGZHENG_50;
    if(s[16]=='9')return ZHONGZHENG_500;
    if(s[16]=='3')return HUSHEN_300;
    #ifdef DEBUG
    log_info("parse index type:");
    log_str(s[16]);
    #endif
}

//this is a call-back function which will receive the curl return value and parse the data in it.
//update the buffer if necessary (when the new data is received) 
size_t write_to_buffer(void *buffer, size_t size, size_t nmemb, void *userp)
{

    int index_f,index_e;
    
    
    std::string data((char*) buffer, size * nmemb);
    std::cout<<"source data:"<<data<<"\n";
    
    
    //Parse the index type;
    index_t index_type;
    index_type=parse_index_type(data.data());
    switch (index_type)
    {
      case SHANGZHENG_50:
          std::cout<<"SHANGZHNEG50"<<std::endl;break;
      case ZHONGZHENG_500:
          std::cout<<"ZHONGZHENG500"<<std::endl;break;
      case HUSHEN_300:
          std::cout<<"HUSHEN300"<<std::endl;break;
      default:std::cout<<"An Error occurred:"<<index_type<<std::endl;break;
          break;
    }

    //Parse the index value
    double update_val=0;
    index_f=data.find_first_of(',');
    index_e=data.find_first_of(',',index_f+1);
    sscanf(data.substr(index_f+1,index_e-index_f-1).data(),"%lf",&update_val);
    
    #ifdef DEBUG
    printf("parsed index value:%lf\n",update_val);
    #endif

    //Parse the update time
    index_e=data.find_last_of(',');    
    index_f=data.find_first_of('-');
    
    std::string uptime_str=data.substr(index_f-4,index_e-index_f+4);
    SADateTime* update_time;
    parse_date_time(uptime_str,&update_time);
    
    //Compare the date time 
    if((*update_time)==(*index_buffer.last_tick_time[index_type])){
      cout<<"redunt data"<<endl;

      pthread_mutex_lock(&mutex_x);
      trade_handler::make_decision(index_type,update_val);
      pthread_mutex_unlock(&mutex_x);

      index_buffer.is_updated[index_type]=false;
    } 
    else{
      cout<<"Got the newer data,recording the data in the common buffer..."<<endl;
      index_buffer.is_updated[index_type]=true;
      *(index_buffer.last_tick_time[index_type])=*update_time;
      index_buffer.val[index_type]=update_val;
      pthread_mutex_lock(&mutex_x);
      trade_handler::make_decision(index_type,update_val);
      pthread_mutex_unlock(&mutex_x);
      free(update_time);
    }
    return size*nmemb;
}
//1.Get the index json data.
//2.Parse the json data and compare the data to judge if the data is newer.
//3.If it is store it in the buffer (in the call back function)
//4.Check if there is newer data.
int share_index::update_val(){
  CURL *curl;
  CURLcode res;

  std::string url_str="http://hq.sinajs.cn/list=sh";
  url_str+=this->post_para[this->get_index_type()];

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url_str.data());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,write_to_buffer);
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
          fprintf(stderr, "curl_easy_perform() failed: %s \n the error code:%d",
          curl_easy_strerror(res),res);

        /* always cleanup */
        curl_easy_cleanup(curl);

    //to-do:we do not check if the data is valid which could be unberable in practice

    //Got the data and store it in the list
    if(index_buffer.is_updated[type]){
      index_eledata temp(*(index_buffer.last_tick_time[type]),index_buffer.val[type]);
      insert_data(temp);
      cout<<"insert the index data success";
      index_buffer.is_updated[type]=false;
    }
  }
  curl_global_cleanup();
  return 0;
}
int share_index::insert_data(index_eledata& e){
  if(market_data.size()==MEM_MAX_SIZE)market_data.pop_front();
  market_data.push_back(e);
  //insert data into the line graph


  LineChartBlockView* tp=init_window->_datapage->getBlockView(this->type+1);
  //database operation
  switch(this->type){
      case SHANGZHENG_50:
          tp->update_line(shangzheng50_count,e.value,0);
          shangzheng50_count+=1.0;
          break;
    case ZHONGZHENG_500:
          tp->update_line(zhongzheng500_count,e.value,0);
          zhongzheng500_count+=1.0;
          break;
    case HUSHEN_300:
          tp->update_line(hushen300_count,e.value,0);
          hushen300_count+=1.0;
          break;
    default:
          log_error("share_index::insert_data:an error occurred while inserting data into the front view.");
          break;
  }

  //insert data into the database
  hfts_db::insert_index_data(this->type,e);

  return 0;
}
share_index::share_index(index_t t,index_val v){
        this->type=t;this->value=v;
        hfts_db::create_index(index_name[t]);
}
void* keep_collecting_data(void* p){
    share_index* t=(share_index*)p;
    while(true){
        t->update_val();
        sleep(2);
    }
}
//Here we start a new thread to keep collecting data
void share_index::start_collecting_data(){
    pthread_create(&tid,NULL,&keep_collecting_data,this);
}
