#ifndef INCLUDE_tlisp_state_h__
#define INCLUDE_tlisp_state_h__
#include "types.h"
/**
 * @file tlisp/state.h
 * @brief Tlisp state  routines
 * @defgroup tlisp_state Tlisp state routines
 * @ingroup Tlisp
 * @{
 */

/** Open a handle to a new state
 * @returns an open state. state must be closed with
 * tlisp_state_close(tlisp_state*).
 */
tlisp_state *tlisp_state_open(void);

/** Close an open tlip state
 * @param state An open tlisp state.
 */
void tlisp_state_close(tlisp_state *state);


/** Load and compile the given buffer.
 * @param state Active state.
 * @param buffer The buffer to parse.
 * @param blen The buffer len.
 * @returns \ref TLISP_RESULT_ERR on failure. 
 * @seealso tlisp_error_next().
 */
tlisp_result_t tlisp_state_loadbuffer(tlisp_state *state, const char *buffer, int blen);

/** Executes a function from the stack 
 * @param state The active state.
 * @param dist The distance  (n - 1 - dist) to the location of the function object from the top of the stack.
 * @param params The total number of function paramaters
 * @param nret_vals The number of values returned; 1 or 0.
 * @returns \ref TLISP_RESULT_ERR on failure.
 * @seealse tlisp_error_next().
 */
tlisp_result_t tlisp_state_call(tlisp_state *state, int dist, int params, int nret_vals);

/** @} */
#endif // !INCLUDE_tlisp_state_h__
