#include "include/common.h"
#include <curl/curl.h>

size_t WriteToString(void *buffer, size_t size, size_t nmemb, void *userp)
{
    double update_val=0;
    std::string data((char*) buffer, size * nmemb);
    int index_f=data.find_first_of(',');
    int index_e=data.find_first_of(',',index_f+1);
    sscanf(data.substr(index_f+1,index_e-index_f-1).data(),"%lf",&update_val);
    printf("%lf",update_val);
    return size*nmemb;
}
int share_index::update_val(){
  CURL *curl;
  CURLcode res;
  std::string url_str="http://hq.sinajs.cn/list=sh";
  std::cout<<"The target url"<<this->post_para[0];
  url_str+=this->post_para[this->get_index_type()];
  std::cout<<"Final str"<<url_str<<std::endl;
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url_str.data());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteToString);
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return 0;
}