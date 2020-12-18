#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#ifdef _MSC_VER
    #define _CRT_SECURE_NO_WARNINGS
#endif

typedef long long int_t;

#define INT_T_MIN  (-9223372036854775807i64 - 1)
#define INT_T_MAX  9223372036854775807i64


#define SHORT_STR_ALLOC_BYTES 24
#define SHORT_STR_LEN_MAX (SHORT_STR_ALLOC_BYTES-2)

#define LIST_RESERVED_ELEMS 10
#define LIST_INCR_FACTOR 1.8

#define DICT_KEY_ALLOC_BYTES 24
#define DICT_RESERVED_NODES 16
