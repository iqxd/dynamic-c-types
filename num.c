#include "num.h"

type_t IntType = { .tp = INT, .clone_func = clone_var , .print_func = print_var};
type_t FloatType = {.tp = FLOAT, .clone_func = clone_var , .print_func = print_var};

var_t* clone_num(num_t n)
{
    return n.type->clone_func((var_t*)&n);
}

void print_num(num_t n)
{
    n.type->print_func((var_t *)&n);
}



