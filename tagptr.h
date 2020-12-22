#include "config.h"

typedef uint64_t tagptr_t;
#define TAG_ALLOC_BITS 8
#define TAG_SHIFT_BITS 56

typedef enum {
    T_NONE=0,
    T_TRUE,
    T_FALSE,
    T_INT,
    T_FLOAT,
    T_STR,
    T_SSTR,
    T_LIST,
    T_DICT
} tag_t;

static inline tagptr_t build_tag_ptr(void* raw, tag_t tag)
{
    return (tagptr_t)raw | ((tagptr_t)tag << TAG_SHIFT_BITS);
}

static inline tag_t get_tag(tagptr_t tp)
{
    return (tag_t)(tp >> TAG_SHIFT_BITS);
}

static inline int32_t get_int(tagptr_t tp)
{
    return (int32_t)(0x00000000FFFFFFFF & tp);
}

static inline void* get_ref(tagptr_t tp)
{
    return (void*)(0x00FFFFFFFFFFFFFF & tp);
}

static inline tagptr_t new_int(int32_t val)
{
    return build_tag_ptr(NULL, T_INT) | (uint32_t)val;
}

static inline tagptr_t new_float(double val)
{
    double* pval = (double*)malloc(sizeof(val));
    *pval = val;
    return build_tag_ptr(pval, T_FLOAT);
}