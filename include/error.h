#ifndef ERROR_H
#define ERROR_H
enum ERROR_TYPE{
    INTERNET_NOT_ALIVE
};
class Error{
    static void parse_error(ERROR_TYPE t);
};
#endif // ERROR_H
