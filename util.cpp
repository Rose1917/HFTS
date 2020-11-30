#include "include/common.h"
using namespace std;
char* double2c(double d){
    char* temp_str=(char*)malloc(ARRAY_SIZE);
	sprintf(temp_str,"%.4lf",d);
    return temp_str;
}
char* int2c(int i){
    char* temp_str=(char*)malloc(ARRAY_SIZE);
	sprintf(temp_str,"%d",i);
    return temp_str;
}
char* float2c(float f){
    char* temp_str=(char*)malloc(ARRAY_SIZE);
	sprintf(temp_str,"%.4f",f);
    return temp_str;
}
char* const2c(char* s){
    char* temp_str=(char*)malloc(ARRAY_SIZE);
	strcpy(temp_str,s);
    return temp_str;
}
//Date functions
int get_year(char* cstr){
    int year;
    string str(cstr+0,4);
    sscanf(str.data(),"%d",&year);
    return year;
}
int get_mon(char* cstr){
    int month;
    string str(cstr+4,2);
    sscanf(str.data(),"%d",&month);
    return month;
}
int get_day(char* cstr){
    int day;
    string str(cstr+6,2);
    sscanf(str.data(),"%d",&day);
    return day;
}
int get_hour(char* cstr){
    int hour;
    string str(cstr+0,2);
    sscanf(str.data(),"%d",&hour);
    return hour;
}
int get_min(char* cstr){
    int min;
    string str(cstr+3,2);
    sscanf(str.data(),"%d",&min);
    return min;
}
int get_sec(char* cstr){
    int sec;
    string str(cstr+6,2);
    sscanf(str.data(),"%d",&sec);
    return sec;
}