#pragma once
#include "num.h"
#include "str.h"
#include "list.h"

#ifdef __GNUC__
#define loc_var_t __attribute__((__cleanup__(Delete))) var_t
#else 
    #define loc_var_t var_t
#endif

#define NewValue(X) _Generic((X), \
    int:set_int, \
    double:set_float, \
    char*:set_str \
)(X)

#define NewList(FIRST_VAR,...) set_list_from_args(FIRST_VAR, ##__VA_ARGS__)
#define NewListFromLen(LEN,...) set_list_from_len_args(LEN, ##__VA_ARGS__)

void Print(var_t);
size_t Size(var_t);
var_t Clone(var_t);
void Delete(var_t*);
