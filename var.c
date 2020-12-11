#include "var.h"

void print_var(var_t* var_p)
{
    type_id tp = var_p->type->tp;
    if (tp == INT)
        printf("%lld\n", ((num_t*)(var_p))->ival);
    else if (tp == FLOAT)
        printf("%lf\n", ((num_t*)(var_p))->fval);
    else if (tp == SSTR)
        printf("%s\n", ((str_t*)(var_p))->sval);
    else if (tp == STR)
        printf("%s\n", ((str_t*)(var_p))->sref);
}