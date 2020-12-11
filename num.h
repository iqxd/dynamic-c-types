#pragma once
#include "var.h"

type_t IntType, FloatType;

#define _to_int_t(x) ((num_t){&IntType, .ival = (int_t)(x)})
#define _to_double(x) ((num_t){&FloatType, .fval = (double)(x)})

// unsigned long long may overflow
#define new_num(x) _Generic((x),  \
    _Bool : _to_int_t(x) ,\
    char : _to_int_t(x) , \
    short   : _to_int_t(x)  , \
    int   : _to_int_t(x)  , \
    long   : _to_int_t(x)  , \
    long long   : _to_int_t(x)  , \
    unsigned char : _to_int_t(x) , \
    unsigned short   : _to_int_t(x)  , \
    unsigned int   : _to_int_t(x)  , \
    unsigned long   : _to_int_t(x)  , \
    unsigned long long   : _to_int_t(x)   , \
    float : _to_double(x), \
    double : _to_double(x), \
    long double : _to_double(x) \
)

void print_num(num_t n);
