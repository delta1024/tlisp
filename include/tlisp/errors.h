#ifndef INCLUDE_tlisp_errors_h
#define INCLUDE_tlisp_errors_h
#include "types.h"
#include <stdio.h>
#include <stdbool.h>
/**
 * @file tlisp/errors.h
 * @brief Tlisp error handling routines
 * @defgroup tlisp_error Tlisp error handling routines
 * @ingroup Tlisp
 * @{
 */

/** Get the next error in the error que.
 * @param[in] state The state to query.
 * @param[out] err ptr to store error info.
 * @returns false if que is empty. Error must be freed with
 * tlisp_error_free() when you are done with it.
 */
bool tlisp_error_next(tlisp_state *state, tlisp_error *err);

/** Dispose of an error
 * @param error The error to despose of.
 */
void tlisp_error_free(tlisp_error *error);

/** Dump all error messages left in the que to a stream.
 * @param state The state to flush.
 * @param stream The file to write to. Each error is seperated by a new line.
 * @returns 0 or -1 if an error is encountered. Error valule is set in erno by
 * the C stdlib.
 */
int tlisp_error_flush(tlisp_state *state, FILE *stream);
/** Report an error
 * @param state The state to add the error to.
 * @param errn Error code to attach to the error.
 * @param message A printf style string containing information about the message.
*/
void tlisp_error_report(tlisp_state *state,int errn, const char *message, ...);
/** @} */
#endif // !INCLUDE_tlisp_errors_h
