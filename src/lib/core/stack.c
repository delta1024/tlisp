#include "stack.h"
#include "tlisp/types.h"
#include <stdbool.h>

void stack_reset(value_stack *stack) {
    stack->stack_top = stack->buffer;
}

tlisp_error_t stack_push(value_stack *stack, tlisp_value value) {
    if (stack->stack_top - stack->buffer == STACK_MAX) {
        return TLISP_ERR_STACK_OVERFLOW;
    }
    *stack->stack_top++ = value;
    return TLISP_ERR_OK;
}
bool stack_pop(value_stack *stack, tlisp_value *value) {
    if (stack->stack_top == stack->buffer)
        return false;
    *value = *--stack->stack_top;
    return true;
}
