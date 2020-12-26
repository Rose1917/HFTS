#ifndef UTIL_H
#define UTIL_H
#define ARRAY_SIZE 3000
char* double2c(double);
char* float2c(float);
char* int2c(int);
char* const2c(char*);
int get_year(char*);
int get_mon(char*);
int get_day(char*);
int get_hour(char*);
int get_min(char*);
int get_sec(char*);
int GbkToUtf8(char *str_str, long unsigned int src_len, char *dst_str, long unsigned int dst_len);
#endif