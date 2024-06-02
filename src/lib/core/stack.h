#ifndef _TLISP_CORE_STACK_H__
#define _TLISP_CORE_STACK_H__
#include "config.h"
#include "tlisp/types.h"
#include <stdint.h>

#define STACK_MAX UINT8_MAX + 1
typedef struct {
    tlisp_value buffer[STACK_MAX];
    tlisp_value *stack_top;
} value_stack;
void stack_reset(value_stack *stack);
/** @returns \ref TLISP_ERR_OK or \ref TLISP_ERR_STACK_OVERFLOW  */
tlisp_error_t stack_push(value_stack *stack, tlisp_value value);
/** Pop a value from the stack
 * @param[out] value
 * @returns true if a value was yeilded
 */
bool stack_pop(value_stack *stack, tlisp_value *value);
#endif // !_TLISP_CORE_STACK_H__
