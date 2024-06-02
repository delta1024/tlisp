#ifndef _TLISP_RUNTIME_STACK_H__
#define _TLISP_RUNTIME_STACK_H__
#include "tlisp/types.h"
#include "config.h"

#define STACK_MAX UINT8_MAX
typedef struct  {
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
#endif // !_TLISP_RUNTIME_STACK_H__
