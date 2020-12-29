#include "var.h"

typefunc_t FuncTable[] = {
    [T_INT] = {.print_func = print_int , .size_func = size_int , .clone_func = clone_int , .delete_func = delete_int },
    [T_PFLOAT] = {.print_func = print_pos_float , .size_func = size_pos_float , .clone_func = clone_pos_float , .delete_func = delete_pos_float},
    [T_NFLOAT] = {.print_func = print_neg_float , .size_func = size_neg_float , .clone_func = clone_neg_float , .delete_func = delete_neg_float},
    [T_SSTR] = {.print_func = print_short_str , .size_func = size_short_str , .clone_func = clone_short_str , .delete_func = delete_short_str},
    [T_LSTR] = {.print_func = print_long_str , .size_func = size_long_str , .clone_func = clone_long_str , .delete_func = delete_long_str}
};

void Print(var_t v)
{
    FuncTable[get_type(v)].print_func(v);
}

size_t Size(var_t v)
{
    return FuncTable[get_type(v)].size_func(v);
}

var_t Clone(var_t v)
{
    return FuncTable[get_type(v)].clone_func(v);
}

void Delete(var_t* v_ref)
{
    FuncTable[get_type(*v_ref)].delete_func(v_ref);
}

// print funcs
void print_int(var_t v)
{
    printf("%16.16llX => %d\n", v, get_int(v));
}

void print_pos_float(var_t v)
{
    printf("%16.16llX => %lf\n", v, get_pos_float(v));
}

void print_neg_float(var_t v)
{
    printf("%16.16llX => %lf\n", v, get_neg_float(v));
}

void print_short_str(var_t v)
{
    printf("%16.16llX => \"%s\"\n", v, get_short_str(v));
}

void print_long_str(var_t v)
{
    printf("%16.16llX => \"%s\"\n", v, get_long_str(v));
}

// size funcs
size_t size_int(var_t v)
{
    return sizeof(v);
}

size_t size_pos_float(var_t v)
{
    return sizeof(v);
}

size_t size_neg_float(var_t v)
{
    return sizeof(v) + sizeof(nfloat_t);
}

size_t size_short_str(var_t v)
{
    return sizeof(v) + sizeof(sstr_t);
}

size_t size_long_str(var_t v)
{
    return sizeof(v) + sizeof(lstr_t) + ((lstr_t*)get_ref(v))->len + 1;
}

// clone funcs
var_t clone_int(var_t v)
{
    return v;
}

var_t clone_pos_float(var_t v)
{
    return v;
}

var_t clone_neg_float(var_t v)
{
    return build_var(_clone_heap_obj(v), T_NFLOAT);
}

var_t clone_short_str(var_t v)
{
    return build_var(_clone_heap_obj(v), T_SSTR);
}

var_t clone_long_str(var_t v)
{
    lstr_t* lstr = (lstr_t*)_clone_heap_obj(v);
    size_t n = *(lstr->refcnt);
    *(lstr->refcnt) = n + 1;
    return build_var(lstr, T_LSTR);
}

// delete funcs
void delete_int(var_t* v_ref)
{
    *v_ref = VAR_NULL;
}

void delete_pos_float(var_t* v_ref)
{
    *v_ref = VAR_NULL;
}

void delete_neg_float(var_t* v_ref)
{
    _delete_heap_obj(v_ref);
}

void delete_short_str(var_t* v_ref)
{
    _delete_heap_obj(v_ref);
}

void delete_long_str(var_t* v_ref)
{
    lstr_t* lstr = (lstr_t*)get_ref(*v_ref);
    size_t n = *(lstr->refcnt);
    if (--n == 0)
    {
        free(lstr->val);
        free(lstr->refcnt);
    }
    else
    {
        *(lstr->refcnt) = n;
    }
    free(lstr);
    *v_ref = VAR_NULL;
}


