#ifndef DEBUG_H
#define DEBUG_H
enum STR_COLOR{
    RED_STR,BLUE_STR,GREEN_STR,YELLOW_STR,NONE_STR
};

//The printf format control string
#define COLOR_NONE "\033[0m" //表示清除前面设置的格式
#define RED "\033[1;31;40m" //40表示背景色为黑色, 1 表示高亮
#define BLUE "\033[1;34;40m"
#define GREEN "\033[1;32;40m"
#define YELLOW "\033[1;33;40m"

//The error code
enum ERROR_CODE{
    CONNECTION_TIME_OUT=2002
};

int log_str(char* str,STR_COLOR color=NONE_STR,int tab_level=0);
int log_str(char* str1,char* str2,STR_COLOR color=NONE_STR,int tab_level=0);
int log_str(int i,STR_COLOR color=NONE_STR,int tab_level=0);
int log_str(char c,STR_COLOR color=NONE_STR,int tab_level=0);

int log_error(char* str,int tab_level=0);
int log_error(char* str1,char* str2,int tab_level=0);
int log_info(char* str,int tab_level=0);
int log_info(char* str1,char* str2,int tab_level=0);

int log_stone(int);
int print_tab(int);


#endif