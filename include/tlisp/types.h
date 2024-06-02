#ifndef INCLUDE_tlisp_types_h
#define INCLUDE_tlisp_types_h

#include <stdbool.h>
/**
 * @file tlisp/types.h
 * @brief libtlisp base types
 * @defgroup tlisp_types libtlisp base types
 * @ingroup Tlisp
 * @{
 */

/** An open state handle. */
typedef struct tlisp_state tlisp_state;

/** Possible error states. */
typedef enum {
    TLISP_ERR_OK    = 0,  /**< No error has occured. */
    TLISP_ERR_NOMEM = -1, /**< Program has run out of memory. */
    TLISP_ERR_UNTERMITATED_STRING =
        -2,               /**< Lexer has encountered an unterminated string */
    TLISP_ERR_STACK_OVERFLOW = -3, /**< Runtime stack overflow */
    TLISP_ERR_WRNG_OPCODE = -4, /**< Runtime encountered an unknown opcode */
} tlisp_error_t;

/** Result from a failable function */
typedef enum {
    TLISP_RESULT_OK = true, /**< No error has occured. */
    TLISP_RESULT_ERR = false, /**< An error has occured. Call \ref tlisp_error_next() to get details */
} tlisp_result_t;

/** A tlisp error value */
typedef struct {
    tlisp_error_t code; /**< The Error code. See \ref tlisp_error_t. */
    char *message;      /**< Assiated error message. */
    int mlen;           /**< Message length. */
} tlisp_error;

 /** The tlisp number type */
typedef double tlisp_number_t;

 /** The underlying type of a list value */
typedef enum tlisp_value_t {
    TLISP_VALUE_NUMBER /**< A number value */
} tlisp_value_t;

 /** A generic list value */
typedef tlisp_number_t tlisp_value;

/** @} */
#endif // !INCLUDE_tlisp_types_h
