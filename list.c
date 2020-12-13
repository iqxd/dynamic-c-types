#include "list.h"

type_t ListType = { .tp = LIST, .print_func = print_var};

list_t* new_list(var_t* vp[], size_t len)
{
    list_t* lp = malloc(sizeof(list_t)+sizeof(var_t*)*len);
    lp->type = &ListType;
    lp->len = len;
    lp->capacity = 10 + len * ListSizeIncrFactor;
    memmove(lp->lref, vp, len);
    return lp;
}

void print_list(list_t* lp)
{
    var_t* vp = lp->lref;
    for (size_t i=0;i<lp->len;i++){
        vp->type->print_func(vp);
    }
}
