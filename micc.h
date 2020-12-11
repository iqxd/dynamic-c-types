#pragma once
#include "var.h"
#include "num.h"

#define print(x) _Generic((x), \
    num_t: print_num \
    )(x)
