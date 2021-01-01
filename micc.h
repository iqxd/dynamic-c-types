#pragma once
#include "num.h"
#include "str.h"

#define New(X) _Generic((X), \
    int:set_int, \
    double:set_float, \
    char*:set_str \
)(X)

void Print(var_t);
size_t Size(var_t);
var_t Clone(var_t);
void Delete(var_t*);