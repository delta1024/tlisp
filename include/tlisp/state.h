#ifndef INCLUDE_tlisp_state_h__
#define INCLUDE_tlisp_state_h__
#include "types.h"
/**
 * @file tlisp/state.h
 * @brief Tlisp state  routines
 * @defgroup tlisp_state Tlisp state  routines
 * @ingroup Tlisp
 * @{
 */

/** Open a handle to a new state
 * @returns an open state. state must be closed with
 * tlisp_state_close(tlisp_state*).
 */
tlisp_state *tlisp_state_open(void);

/** Close an open tlisp state
 * @param state An open tlisp state.
 */
void tlisp_state_close(tlisp_state *state);
/** @} */
#endif // !INCLUDE_tlisp_state_h__
