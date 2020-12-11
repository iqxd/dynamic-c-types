#pragma once
#include "var.h"
#include "num.h"
#include "str.h"

#define print(x) _Generic((x), \
    num_t: print_num, \
    str_t: print_str \
    )(x)
