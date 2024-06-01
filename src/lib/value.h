#ifndef _TLISP_VALUE_H__
#define _TLISP_VALUE_H__
#include "tlisp/types.h"
#include "memory.h"
typedef struct {
    tlisp_value *entries;
    int count;
    int capacity;
}value_array ;
void value_array_init(value_array *array);
void value_array_write(value_array *array, tlisp_value value, allocator *allocator);
void value_array_free(value_array *array, allocator *allocator);
#endif // !_TLISP_VALUE_H__
