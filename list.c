#include "list.h"

type_t ListType = { .tp = LIST, .print_func = print_var , .clone_func = clone_var , .delete_func = delete_var };

list_t* new_list(var_t* vp[], size_t len)
{
    size_t capacity =  10 + len * ListSizeIncrFactor;
    list_t* lp = malloc(sizeof(list_t)+sizeof(var_t*)*capacity);
    lp->type = &ListType;
    lp->len = len;
    lp->capacity = capacity;
    memmove(lp->lref, vp, sizeof(var_t*)*len);
    return lp;
}

var_t* clone_list(list_t *lp)
{
    return lp->type->clone_func((var_t*)lp);
}

void delete_list(list_t *lp)
{
    lp->type->delete_func((var_t*)lp);
}

void print_list(list_t* lp)
{
    lp->type->print_func((var_t *)lp);
}
