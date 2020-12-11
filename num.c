#include "num.h"

type_t IntType = { .tp = INT, .print_func = print_var};
type_t FloatType = {.tp = FLOAT, .print_func = print_var};

void print_num(num_t n)
{
    n.type->print_func((var_t *)&n);
}



