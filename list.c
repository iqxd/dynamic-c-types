#include "list.h"

type_t ListType = { .tp = LIST, .print_func = print_var , .clone_func = clone_var , .delete_func = delete_var };

list_t* new_list(var_t** vp_arr, size_t len)
{
    size_t capacity =  LIST_RESERVED_ELEMS + len * LIST_INCR_FACTOR;
    list_t* lp = malloc(sizeof(list_t)+sizeof(var_t*)*capacity);
    lp->type = &ListType;
    lp->len = len;
    lp->capacity = capacity;
    for (size_t i =0 ; i<lp->len; i++) {
        lp->lref[i] = vp_arr[i]->type->clone_func(vp_arr[i]);
    }
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

void list_add(list_t* lp,var_t* vp)
{
    if( lp->len+1 > lp->capacity )
    {
        size_t new_capacity = lp->capacity * LIST_INCR_FACTOR;
        lp = realloc(lp, new_capacity);
        lp->capacity = new_capacity;
    }
    lp->lref[lp->len] = vp->type->clone_func(vp);
    lp->len++;
}

var_t* list_get(list_t* lp,size_t index)
{
    if (index > lp->len - 1) return (var_t*)NULL;
    var_t* vp = lp->lref[index];
    return vp->type->clone_func(vp);
}

void list_update(list_t* lp,size_t index,var_t* new_vp)
{
    if (index > lp->len - 1) return;
    var_t* vp = lp->lref[index];
    vp->type->delete_func(vp);
    vp = new_vp->type->clone_func(new_vp);
}

void list_remove(list_t* lp, size_t index)
{
    if (index > lp->len - 1) return;
    var_t* vp = lp->lref[index];
    vp->type->delete_func(vp);
    for(size_t i=index;i<lp->len-1;i++)
    {
        lp->lref[i] = lp->lref[i + 1];
    }
    lp->lref[lp->len] = NULL;
    lp->len--;
}

void list_pop(list_t *lp)
{
    list_remove(lp, lp->len - 1);
}

void list_clear(list_t *lp)
{
    for (size_t i =0 ; i<lp->len; i++) {
        var_t* vp = lp->lref[i];
        vp->type->delete_func(vp);
        vp = NULL;
    }
    lp->len = 0;
}