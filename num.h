#pragma once
#include "var.h"

type_t IntType;

#define new_num(x) _Generic((x),  \
    int : ((num_t){&IntType,.ival = (int_t)(x)}) , \
    double : ((num_t){&IntType,.fval = (double)(x)}) \
)


