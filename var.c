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
    else if(tp==LIST) {
        list_t* lp = (list_t*)var_p;
        printf("[\n");
        for (size_t i = 0; i < lp->len;i++)
            print_var(lp->lref[i]);
        printf("]\n");
    }
}

var_t* clone_var(var_t* var_p)
{
    type_id tp = var_p->type->tp;
    if(tp==INT || tp==FLOAT){
        num_t* np_dup = malloc(sizeof(num_t));
        *np_dup = *((num_t*)var_p);
        return (var_t*)np_dup;
    }
    else if(tp==SSTR){
        str_t* sp_dup = malloc(sizeof(str_t));
        *sp_dup = *((str_t*)var_p);
        return (var_t*)sp_dup;
    }
    else if(tp==STR){
        str_t* sp_dup = malloc(sizeof(str_t));
        sp_dup->type = var_p->type;
        sp_dup->sref = strdup(((str_t*)var_p)->sref);
        return (var_t*)sp_dup;
    }
    else if(tp==LIST){
        list_t* lp = (list_t*)var_p;
        size_t len = sizeof(list_t) + sizeof(var_t*) * (lp->capacity);
        list_t* lp_dup = malloc(len);
        *lp_dup = *lp;
        for (size_t i = 0; i < lp->len; i++) {
            var_t* vp = lp->lref[i];
            if (vp->type->clone_func) 
                lp_dup->lref[i] = vp->type->clone_func(vp);
        }
        return (var_t*)lp_dup;
    }
}

void delete_var(var_t* var_p)
{
    type_id tp = var_p->type->tp;
    if (tp==STR){
        free(((str_t*)var_p)->sref);
    }
    else if(tp==LIST) {
        list_t* lp = (list_t*)var_p;
        for (size_t i = 0 ; i <lp->len; i++){
            var_t* vp = lp->lref[i];
            if (vp->type->delete_func) 
                vp->type->delete_func(vp);
            else
                free(vp);
        }
        free(lp);
    }     
}