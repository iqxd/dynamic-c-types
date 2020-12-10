#include "micc.h"

static void print(var_t var)
{
    var.type->print_func(&var);
}