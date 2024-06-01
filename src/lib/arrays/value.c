#include "value.h"
#include "core/memory.h"
#include "tlisp/types.h"
#include <stddef.h>

void value_array_init(value_array *array) {
    array->count = array->capacity = 0;
    array->entries = NULL;
}
void value_array_free(value_array *array, allocator *allocator) {
    tfree(allocator, array->entries, sizeof(tlisp_value) * array->capacity);
    value_array_init(array);
}

void value_array_write(value_array *array, tlisp_value value, allocator *allocator) {
    if (array->count + 1 > array->capacity) {
        int ocap = array->capacity;
        array->capacity = ocap < 8 ? 8 : ocap * 2;
        array->entries = trealloc(allocator, array->entries, sizeof(tlisp_value) * ocap, 
                                  sizeof(tlisp_value) * array->capacity);
    }
    array->entries[array->count++] = value;
}
