#include "include/common.h"

//Print the string with color.
int log_str(char* str,STR_COLOR color,int tab_level)
{
    if(!tab_level)print_tab(tab_level);
    switch (color){
        case RED_STR:
            printf(RED "%s" COLOR_NONE,str);
            break;
        case BLUE_STR:
            printf(BLUE "%s" COLOR_NONE,str);
            break;
        case GREEN_STR:
            printf(GREEN "%s" COLOR_NONE,str);
            break;
        case YELLOW_STR:
            printf(YELLOW "%s" COLOR_NONE,str);
            break;
        case NONE_STR:
            printf("%s",str);
            break;
        default:
            break;
        
    }
    printf("\n");
    return 0; 
}
int log_str(char* str1,char* str2,STR_COLOR color,int tab_level)
{
    if(!tab_level)print_tab(tab_level);
    switch (color){
        case RED_STR:
            printf(RED "%s %s" COLOR_NONE,str1,str2);
            break;
        case BLUE_STR:
            printf(BLUE "%s %s" COLOR_NONE,str1,str2);
            break;
        case GREEN_STR:
            printf(GREEN "%s %s" COLOR_NONE,str1,str2);
            break;
        case YELLOW_STR:
            printf(YELLOW "%s %s" COLOR_NONE,str1,str2);
            break;
        case NONE_STR:
            printf("%s %s",str1,str2);
            break;
        default:
            break;
        
    }
    printf("\n");
    return 0; 
}
int log_str(int str,STR_COLOR color,int tab_level)
{
    if(!tab_level)print_tab(tab_level);
    switch (color){
        case RED_STR:
            printf(RED "%d" COLOR_NONE,str);
            break;
        case BLUE_STR:
            printf(BLUE "%d" COLOR_NONE,str);
            break;
        case GREEN_STR:
            printf(GREEN "%d" COLOR_NONE,str);
            break;
        case YELLOW_STR:
            printf(YELLOW "%d" COLOR_NONE,str);
            break;
        case NONE_STR:
            printf("%d",str);
            break;
        default:
            break;
        
    }
    printf("\n");
    return 0; 
}
int log_str(char str,STR_COLOR color,int tab_level)
{
    if(!tab_level)print_tab(tab_level);
    switch (color){
        case RED_STR:
            printf(RED "%c" COLOR_NONE,str);
            break;
        case BLUE_STR:
            printf(BLUE "%c" COLOR_NONE,str);
            break;
        case GREEN_STR:
            printf(GREEN "%c" COLOR_NONE,str);
            break;
        case YELLOW_STR:
            printf(YELLOW "%c" COLOR_NONE,str);
            break;
        case NONE_STR:
            printf("%c",str);
            break;
        default:
            break;
        
    }
    printf("\n");
    return 0; 
}

int log_error(char* str,int tab_level){
    return log_str(str,RED_STR,tab_level);
}
int log_error(char* str1,char* str2,int tab_level){
    return log_str(str1,str2,RED_STR,tab_level);
}
int log_info(char* str,int tab_level){
    return log_str(str,BLUE_STR,tab_level);
}
int log_info(char* str1,char* str2,int tab_level){
    return log_str(str1,str2,BLUE_STR,tab_level);
}
int print_tab(int tab_level){
    for(int i=0;i<tab_level;i++){
        std::cout<<"\t";
    }
}