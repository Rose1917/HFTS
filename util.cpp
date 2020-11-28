#include "include/common.h"
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

