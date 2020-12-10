#include "var.h"

void print_var(var_t* var_p)
{
    type_id tp = var_p->type->tp;
    if (tp==INT)
        printf("%lld\n", ((num_t *)(var_p))->ival);
    else if(tp==UINT)
        printf("%llu\n", ((num_t *)(var_p))->uval);
    else if(tp==FLOAT)
        printf("%lf\n", ((num_t *)(var_p))->fval);
}