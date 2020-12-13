#pragma once
#include "var.h"
#include "num.h"
#include "str.h"
#include "list.h"

#define print(x) _Generic((x), \
    num_t: print_num, \
    str_t: print_str, \
    list_t*: print_list \
    )(x)
