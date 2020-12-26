#include "config.h"

typedef uint64_t tagptr_t;
#define TAG_ALLOC_BITS 9
#define TAG_SHIFT_BITS 55
#define POS_FLOAT_SHIFT_BITS 1
#define INT_BITS_MASK       0x00000000FFFFFFFF
#define REF_BITS_MASK       0x007FFFFFFFFFFFFF
#define POS_FLOAT_BITS_MASK 0x7FFFFFFFFFFFFFFF

typedef enum {
    T_INT = 0 ,
    T_NONE,
    T_TRUE,
    T_FALSE,
    T_NEG_FLOAT,
    T_LSTR,
    T_SSTR,
    T_LIST,
    T_DICT,
    T_POS_FLOAT = 256
} tag_t;

static inline tagptr_t build_tag_ptr(void* raw, tag_t tag)
{
    return (tagptr_t)raw | ((tagptr_t)tag << TAG_SHIFT_BITS);
}

static inline tag_t get_tag(tagptr_t tp)
{
    return (tag_t)(tp >> TAG_SHIFT_BITS);
}

static inline void* get_ref(tagptr_t tp)
{
    return (void*)(tp & REF_BITS_MASK );
}

static inline tagptr_t new_int(int32_t val)
{
    return build_tag_ptr(NULL, T_INT) | (uint32_t)val;
}

static inline int32_t get_int(tagptr_t tp)
{
    return (int32_t)(tp & INT_BITS_MASK);
}

static inline tagptr_t new_float(double val)
{
    if (val < 0)
    {
        double* pval = (double*)malloc(sizeof(val));
        *pval = val;
        return build_tag_ptr(pval, T_NEG_FLOAT);
    }
    // most floating numbers used in common case are positive, 
    // so use tagged value in the pointer to avoid heap allocation.
    return (*(tagptr_t*)&val) | build_tag_ptr(NULL, T_POS_FLOAT);  
}

static inline double get_float(tagptr_t tp)
{
    tag_t tag = get_tag(tp);
    if (tag >= T_POS_FLOAT)
        return *(double*)(&(tagptr_t){ tp & POS_FLOAT_BITS_MASK });
    else if (tag == T_NEG_FLOAT)
        return *(double*)get_ref(tp);
}

typedef struct {
    char val[23];
    char len;
} tsstr_t;

typedef struct {
    size_t len;
    char* val;
} tlstr_t;

typedef struct {
    size_t len;
    tagptr_t* elem;
    size_t alloc;
} tlist_t;

static inline tagptr_t new_string(const char* val)
{
    size_t len = strlen(val);
    if ( len < 23 ){
        tsstr_t* raw = malloc(sizeof(tsstr_t));
        strcpy(raw->val, val);
        raw->len = len;
        return build_tag_ptr(raw, T_SSTR);
    } 
    else 
    {
        tlstr_t* raw = malloc(sizeof(tlstr_t));
        raw->len = len;
        raw->val = malloc((len + 1) * sizeof(char));
        strcpy(raw->val, val);
        return build_tag_ptr(raw, T_LSTR);
    } 
}

static inline char* get_string(tagptr_t tp)
{
    tag_t tag = get_tag(tp);
    void* ref = get_ref(tp);
    if (tag == T_SSTR)
        return ((tsstr_t*)ref)->val;
    else if (tag == T_LSTR)
        return ((tlstr_t*)ref)->val;
}

