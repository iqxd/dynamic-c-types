#include "tagptr.h"

// print funcs
void print_int(tagptr_t tp)
{
    printf("%16.16llx => %d\n", tp, get_int(tp));
}

void print_pos_float(tagptr_t tp)
{
    printf("%16.16llx => %lf\n", tp, get_pos_float(tp));
}

void print_neg_float(tagptr_t tp)
{
    printf("%16.16llx => %lf\n", tp, get_neg_float(tp));
}

void print_short_str(tagptr_t tp)
{
    printf("%16.16llx => %s\n", tp, get_short_str(tp));
}

void print_long_str(tagptr_t tp)
{
    printf("%16.16llx => %s\n", tp, get_long_str(tp));
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


// tagfunc_t tagfunc_arr[] = {
//     [T_INT] = {.print_func = },
//     [T_POS_FLOAT] = {},
//     [T_NEG_FLOAT] = {},
//     [T_SSTR] = {},
//     [T_LSTR] = {}
// };

