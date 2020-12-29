#include "tagptr.h"

tagfunc_t tagfunc_arr[] = {
    [T_INT] = {.print_func = print_int , .size_func = size_int , .clone_func = clone_int , .delete_func = delete_int },
    [T_POS_FLOAT] = {.print_func = print_pos_float , .size_func = size_pos_float , .clone_func = clone_pos_float , .delete_func = delete_pos_float},
    [T_NEG_FLOAT] = {.print_func = print_neg_float , .size_func = size_neg_float , .clone_func = clone_neg_float , .delete_func = delete_neg_float},
    [T_SSTR] = {.print_func = print_short_str , .size_func = size_short_str , .clone_func = clone_short_str , .delete_func = delete_short_str},
    [T_LSTR] = {.print_func = print_long_str , .size_func = size_long_str , .clone_func = clone_long_str , .delete_func = delete_long_str}
};

void Print(tagptr_t tp)
{
    tagfunc_arr[get_tag(tp)].print_func(tp);
}

size_t Size(tagptr_t tp)
{
    return tagfunc_arr[get_tag(tp)].size_func(tp);
}

tagptr_t Clone(tagptr_t tp)
{
    return tagfunc_arr[get_tag(tp)].clone_func(tp);
}

void Delete(tagptr_t* reftp)
{
    return tagfunc_arr[get_tag(*reftp)].delete_func(reftp);
}

// print funcs
void print_int(tagptr_t tp)
{
    printf("%16.16llX => %d\n", tp, get_int(tp));
}

void print_pos_float(tagptr_t tp)
{
    printf("%16.16llX => %lf\n", tp, get_pos_float(tp));
}

void print_neg_float(tagptr_t tp)
{
    printf("%16.16llX => %lf\n", tp, get_neg_float(tp));
}

void print_short_str(tagptr_t tp)
{
    printf("%16.16llX => \"%s\"\n", tp, get_short_str(tp));
}

void print_long_str(tagptr_t tp)
{
    printf("%16.16llX => \"%s\"\n", tp, get_long_str(tp));
}

// size funcs
size_t size_int(tagptr_t tp)
{
    return sizeof(tp);
}

size_t size_pos_float(tagptr_t tp)
{
    return sizeof(tp);
}

size_t size_neg_float(tagptr_t tp)
{
    return sizeof(tp) + sizeof(tnfloat_t);
}

size_t size_short_str(tagptr_t tp)
{
    return sizeof(tp) + sizeof(tsstr_t);
}

size_t size_long_str(tagptr_t tp)
{
    return sizeof(tp) + sizeof(tlstr_t) + ((tlstr_t*)get_ref(tp))->len + 1;
}

// clone funcs
tagptr_t clone_int(tagptr_t tp)
{
    return tp;
}

tagptr_t clone_pos_float(tagptr_t tp)
{
    return tp;
}

tagptr_t clone_neg_float(tagptr_t tp)
{
    return build_tag_ptr(_clone_heap_obj(tp), T_NEG_FLOAT);
}

tagptr_t clone_short_str(tagptr_t tp)
{
    return build_tag_ptr(_clone_heap_obj(tp), T_SSTR);
}

tagptr_t clone_long_str(tagptr_t tp)
{
    tlstr_t* lstr = (tlstr_t*)_clone_heap_obj(tp);
    size_t n = *(lstr->refcnt);
    *(lstr->refcnt) = n + 1;
    return build_tag_ptr(lstr, T_LSTR);
}

// delete funcs
void delete_int(tagptr_t* tp)
{
    *tp = TAG_NULL;
}

void delete_pos_float(tagptr_t* tp)
{
    *tp = TAG_NULL;
}

void delete_neg_float(tagptr_t* tp)
{
    _delete_heap_obj(tp);
}

void delete_short_str(tagptr_t* tp)
{
    _delete_heap_obj(tp);
}

void delete_long_str(tagptr_t* tp)
{
    tlstr_t* lstr = (tlstr_t*)get_ref(*tp);
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
    *tp = TAG_NULL;
}


