#include "micc.h"

typedef struct {
    size_t(*size_func)(var_t);
    void (*print_func)(var_t);
    var_t(*clone_func)(var_t);
    void (*delete_func)(var_t*);
} typefunc_t;

static typefunc_t FuncTable[POS_FLOAT_TAG_LEAST + 1] = {
    [T_INT] = {.print_func = print_int , .size_func = size_tag_var , .clone_func = clone_tag_var , .delete_func = delete_tag_var },
    [T_NULL] = {.print_func = print_null , .size_func = size_tag_var , .clone_func = clone_tag_var  },
    [T_PFLOAT] = {.print_func = print_pos_float , .size_func = size_tag_var , .clone_func = clone_tag_var , .delete_func = delete_tag_var},
    [T_NFLOAT] = {.print_func = print_neg_float , .size_func = size_heap_var , .clone_func = clone_heap_var , .delete_func = delete_heap_var},
    [T_SSTR] = {.print_func = print_short_str , .size_func = size_heap_var , .clone_func = clone_heap_var , .delete_func = delete_heap_var},
    [T_LSTR] = {.print_func = print_long_str , .size_func = size_long_str , .clone_func = clone_long_str , .delete_func = delete_long_str}
};

void Print(var_t v)
{
    void(*f)(var_t) = FuncTable[get_type(v)].print_func;
    if(f) f(v);
}

size_t Size(var_t v)
{
    size_t(*f)(var_t) = FuncTable[get_type(v)].size_func;
    return f ? f(v) : 0;
}

var_t Clone(var_t v)
{
    var_t(*f)(var_t) = FuncTable[get_type(v)].clone_func;
    return f ? f(v) : VAR_NULL;
}

void Delete(var_t* v_ref)
{
    void(*f)(var_t*) = FuncTable[get_type(*v_ref)].delete_func;
    if (f) f(v_ref);
}






