#include "tlisp/errors.h"
#include "tlisp/state.h"
#include "tlisp/types.h"
#include "unity.h"
#include "unity_internals.h"
#include <string.h>
#include <tlisp.h>
static tlisp_state *state;
static const char *message = "unterminated string";
static tlisp_error error;

void setUp() {
    state         = tlisp_state_open();
    error.message = NULL;
}
void tearDown() {
    if (error.message != NULL) {
        tlisp_error_free(&error);
    }
    tlisp_state_close(state);
}
#ifdef CMAKE_BUILD_TESTS
int errAdd(void) {
#else
void errAdd(void) {
#endif /* ifdef CMAKE_BUILD_TESTS */
    tlisp_error_report(state, TLISP_ERR_UNTERMITATED_STRING, message);
    TEST_ASSERT_MESSAGE(tlisp_error_next(state, &error),
                        "Could not get error from state");
    TEST_ASSERT_EQUAL_INT_MESSAGE(TLISP_ERR_UNTERMITATED_STRING, error.code,
                                  "wrong error code");
    int err_len = strlen(message);
    TEST_ASSERT_EQUAL_INT_MESSAGE(err_len, error.mlen, "Wrong error code");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE(message, error.message, error.mlen,
                                         "Wrong error message");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(errAdd);
    UNITY_END();
}
