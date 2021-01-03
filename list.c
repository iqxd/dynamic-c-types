#include "list.h"
#include "micc.h"

void print_list(var_t v)
{
    list_t* list = get_ref(v);
    printf("%16.16llX => [\n",v);
    for (size_t i = 0; i < list->len; i++)
    {
        printf("\t");
        Print(list->elems[i]);
    }
    printf("]\n");
}

var_t set_list(var_t v_arr[], size_t len)
{
    list_t* raw = _new_heap_obj();
    size_t alloc = LIST_RESERVED_ELEMS + (size_t)(len * LIST_INCR_FACTOR);
    raw->elems = checked_malloc(alloc * sizeof(var_t));
    raw->len = len;
    raw->alloc = alloc;
    for (size_t i = 0; i < len; i++) {
        raw->elems[i] = Clone(v_arr[i]);
    }
    return build_var(raw, T_LIST);
}

size_t size_list(var_t v)
{
    list_t* list = get_ref(v);
    size_t size_elems = 0;
    for (size_t i = 0; i < list->len; i++)
        size_elems += Size(list->elems[i]);
    return size_heap_var(v) + size_elems + (list->alloc - list->len) * sizeof(var_t);
}

var_t clone_list(var_t v)
{
    list_t* list = get_ref(v);
    list_t* raw = _new_heap_obj();
    raw->len = list->len;
    raw->alloc = list->alloc;
    raw->elems = checked_malloc(raw->alloc * sizeof(var_t));
    for (size_t i = 0; i < raw->len; i++)
        raw->elems[i] = Clone(list->elems[i]);
    return build_var(raw, T_LIST);
}

void delete_list(var_t* v_ref)
{
    list_t* list = get_ref(*v_ref);
    for (size_t i = 0; i < list->len; i++)
        Delete(&(list->elems[i]));
    free(list->elems);
    free(list);
    *v_ref = VAR_NULL;
}

void list_add(var_t v, var_t v_add)
{
    list_t* list = get_ref(v);
    if (++list->len > list->alloc)
    {
        size_t new_alloc = (size_t)(list->alloc * LIST_INCR_FACTOR);
        list->elems = checked_realloc(list->elems, new_alloc);
        list->alloc = new_alloc;
    }
    list->elems[list->len-1] = Clone(v_add);
}

var_t list_get(var_t v, size_t index)
{
    list_t* list = get_ref(v);
    if (index > list->len - 1) list_index_error(index, list->len);
    return Clone(list->elems[index]);
}

void list_update(var_t v, size_t index, var_t v_update)
{
    list_t* list = get_ref(v);
    if (index > list->len - 1) list_index_error(index, list->len);
    Delete(&(list->elems[index]));
    list->elems[index] = Clone(v_update);
}

void list_remove(var_t v, size_t index)
{
    list_t* list = get_ref(v);
    if (index > list->len - 1) list_index_error(index, list->len);
    Delete(&(list->elems[index]));
    for (size_t i = index;i < list->len - 1;i++)
        list->elems[i] = list->elems[i + 1];
    list->len--;
}

var_t list_pop(var_t v)
{
    list_t* list = get_ref(v);
    if (list->len == 0) list_index_error(0, 0);
    return list->elems[(list->len--) - 1];
}

void list_clear(var_t v)
{
    list_t* list = get_ref(v);
    for (size_t i = 0; i < list->len; i++) {
        Delete(&(list->elems[i]));
    }
    list->len = 0;
}

bool list_empty(var_t v)
{
    list_t* list = get_ref(v);
    return list->len > 0 ? false : true;
}
