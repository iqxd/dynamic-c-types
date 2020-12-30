#include "var.h"

// print funcs
static void print_int(var_t);
static void print_null(var_t);
static void print_pos_float(var_t);
static void print_neg_float(var_t);
static void print_short_str(var_t);
static void print_long_str(var_t);

// size funcs
static size_t size_tag_var(var_t);
static size_t size_heap_var(var_t);
static size_t size_long_str(var_t);

// clone funcs
static var_t clone_tag_var(var_t);
static var_t clone_heap_var(var_t);
static var_t clone_long_str(var_t);

// delete funcs
static void delete_tag_var(var_t*);
static void delete_heap_var(var_t*);
static void delete_long_str(var_t*);

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

// print funcs
static void print_int(var_t v)
{
    printf("%16.16llX => %d\n", v, get_int(v));
}

static void print_null(var_t v)
{
    printf("%16.16llX => %s\n", v, "NULL");
}

static void print_pos_float(var_t v)
{
    printf("%16.16llX => %lf\n", v, get_pos_float(v));
}

static void print_neg_float(var_t v)
{
    printf("%16.16llX => %lf\n", v, get_neg_float(v));
}

static void print_short_str(var_t v)
{
    printf("%16.16llX => \"%s\"\n", v, get_short_str(v));
}

static void print_long_str(var_t v)
{
    printf("%16.16llX => \"%s\"\n", v, get_long_str(v));
}

// size funcs
static size_t size_tag_var(var_t v)
{
    return sizeof(v);
}

static size_t size_heap_var(var_t v)
{
    return sizeof(v) + HEAP_OBJECT_BYTES;
}

static size_t size_long_str(var_t v)
{
    lstr_t* lstr = get_ref(v);
    return size_heap_var(v) + (lstr->len + 1) + sizeof(*(lstr->refcnt));
}

// clone funcs
static var_t clone_tag_var(var_t v)
{
    return v;
}

static var_t clone_heap_var(var_t v)
{
    return build_var(_clone_heap_obj(v) , get_type(v));
}

static var_t clone_long_str(var_t v)
{
    lstr_t* lstr = (lstr_t*)_clone_heap_obj(v);
    size_t n = *(lstr->refcnt);
    *(lstr->refcnt) = n + 1;
    return build_var(lstr, T_LSTR);
}

// delete funcs
static void delete_tag_var(var_t* v_ref)
{
    *v_ref = VAR_NULL;
}

static void delete_heap_var(var_t* v_ref)
{
    free(get_ref(*v_ref));
    *v_ref = VAR_NULL;
}

static void delete_long_str(var_t* v_ref)
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


