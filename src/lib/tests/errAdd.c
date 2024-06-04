#include "test_common.h"
#include "tlisp/errors.h"
#include "tlisp/state.h"
#include "tlisp/types.h"
#include <string.h>
#include <tlisp.h>
static tlisp_state *state;
static const char *message = "unterminated string";
static tlisp_error error;
#ifdef CMAKE_BUILD_TESTS
int errAdd(void) {
#else
int main() {
#endif /* ifdef CMAKE_BUILD_TESTS */

    state = tlisp_state_open();
    tlisp_error_report(state, TLISP_ERR_UNTERMITATED_STRING, message);

    if (!tlisp_error_next(state, &error)) {
        test_fail("Could not get error from state");
        goto defer;
    }

    if (error.code != TLISP_ERR_UNTERMITATED_STRING) {
        test_fail("Wrong error code; expected %d, got %d",
                  TLISP_ERR_UNTERMITATED_STRING, error.code);
        goto defer_err;
    }

    int err_len = strlen(message);
    if (error.mlen != err_len) {
        test_fail("Wrong error len; expected %d, got %d", err_len, error.mlen);
        goto defer_err;
    }

    if (memcmp(message, error.message, error.mlen) != 0) {
        test_fail("Wrong error message; expected %s, get %.*s", message,
                  error.mlen, error.message);
        goto defer_err;
    }
    test_pass();

defer_err:
    tlisp_error_free(&error);
defer:
    tlisp_state_close(state);
    return 0;
}
