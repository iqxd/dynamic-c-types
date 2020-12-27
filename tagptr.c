#include "tagptr.h"

// print funcs
void print_int(tagptr_t tp)
{
    printf("%16.16llx => %d\n",tp, get_int(tp));
}

void print_pos_float(tagptr_t tp)
{
    printf("%16.16llx => %lf\n",tp, get_pos_float(tp));
}

void print_neg_float(tagptr_t tp)
{
    printf("%16.16llx => %lf\n",tp, get_neg_float(tp));
}

void print_short_str(tagptr_t tp)
{
    printf("%16.16llx => %s\n",tp, get_short_str(tp));
}

void print_long_str(tagptr_t tp)
{
    printf("%16.16llx => %s\n",tp, get_long_str(tp));
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
    return sizeof(tp) + sizeof(tlstr_t) + ((tlstr_t*)get_ref(tp))->len+1;
}

tagfunc_t tagfunc_arr[] = {
    [T_INT] = {},
    [T_POS_FLOAT] = {},
    [T_NEG_FLOAT] = {},
    [T_SSTR] = {},
    [T_LSTR] = {}
};

