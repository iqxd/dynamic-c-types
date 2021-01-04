#pragma once
#include "var.h"

#define INT_BITS_MASK       0x00000000FFFFFFFF
#define POS_FLOAT_BITS_MASK 0x7FFFFFFFFFFFFFFF

typedef struct {
    _Alignas(8) double val;
    _Alignas(8) void* unused1;
    _Alignas(8) void* unused2;
} nfloat_t;

static_assert(sizeof(nfloat_t) == HEAP_OBJECT_BYTES, "");

static inline var_t set_int(int32_t val)
{
    return build_var(NULL, T_INT) | (uint32_t)val;
}

static inline int32_t get_int(var_t v)
{
    return (int32_t)(v & INT_BITS_MASK);
}

static inline var_t set_float(double val)
{
    if (val < 0)
    {
        nfloat_t* raw = checked_malloc(sizeof(nfloat_t));
        raw->val = val;
        return build_var(raw, T_NFLOAT);
    }
    // most floating numbers used in common case are positive, 
    // so use tagged value in the pointer to avoid heap allocation.
    return (*(var_t*)&val) | build_var(NULL, T_PFLOAT);
}

static inline double get_pos_float(var_t v)
{
    return *(double*)(&(var_t) { v & POS_FLOAT_BITS_MASK });
}

static inline double get_neg_float(var_t v)
{
    return *(double*)get_ref(v);
}


static inline void print_int(var_t v)
{
    printf("%16.16llX => %d\n", v, get_int(v));
}

static inline void print_pos_float(var_t v)
{
    printf("%16.16llX => %lf\n", v, get_pos_float(v));
}

static inline void print_neg_float(var_t v)
{
    printf("%16.16llX => %lf\n", v, get_neg_float(v));
}
