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

#define HEAP_OBJECT_BYTES 24

#define SHORT_STR_ALLOC_BYTES 23

#define LIST_RESERVED_ELEMS 10
#define LIST_INCR_FACTOR 1.8

#define DICT_KEY_ALLOC_BYTES 24
#define DICT_RESERVED_NODES 16
