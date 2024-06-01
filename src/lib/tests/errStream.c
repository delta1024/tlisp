#include "tlisp/errors.h"
#include "tlisp/types.h"
#include "errors.h"
#include "test_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static const char *message = "unterminated string";
int errStream(void) {
    error_array array = {NULL};
    FILE *handle = error_openstream(&array);
    error_adderror(handle, TLISP_ERR_UNTERMITATED_STRING,message);
    if (array.count != 1) {
        test_fail("Wrong array count");
        goto defer;
    }
    tlisp_error *error = &array.errors[0];
    if (error->code != TLISP_ERR_UNTERMITATED_STRING) {
        test_fail("Wrong error code; expected %d, got %d", TLISP_ERR_UNTERMITATED_STRING, error->code);
        goto defer_err;
    }

    int err_len = strlen(message);
    if (error->mlen != err_len) {
        test_fail("Wrong error len; expected %d, got %d", err_len, error->mlen);
        goto defer_err;
    }

    if (memcmp(message, error->message, error->mlen) != 0) {
        test_fail("Wrong error message; expected %s, get %.*s", message, error->mlen, error->message );
        goto defer_err;
    }
    test_pass();
defer_err:
    tlisp_error_free(error);
    free(array.errors);
defer:
    fclose(handle);
    return 0;
}
