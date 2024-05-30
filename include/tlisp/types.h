#ifndef INCLUDE_tlisp_types_h
#define INCLUDE_tlisp_types_h

/**
 * @file tlisp/types.h
 * @brief libtlisp base types
 * @ingroup Tlisp
 * @{
 */

/** An open state handle. */
typedef struct tlisp_state tlisp_state;

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
