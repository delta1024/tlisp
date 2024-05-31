#include <string.h>
#include <tlisp.h>
#include "tlisp/errors.h"
#include "tlisp/types.h"
#include "unity.h"
#include "unity_internals.h"
tlisp_state *state;
    const char *message = "unterminated string";
    tlisp_error error;
void setUp() {
    state = tlisp_state_open();
    error.message = NULL;
}
void tearDown() {
    tlisp_state_close(state);
    if (error.message != NULL) {
        tlisp_error_free(&error);
    }
}
void test_ErrorAdd() {
    tlisp_error_report(state, TLISP_ERR_UNTERMITATED_STRING, message);
    TEST_ASSERT(tlisp_error_next(state, &error));
    TEST_ASSERT(error.code == TLISP_ERR_UNTERMITATED_STRING);
    TEST_ASSERT(strlen(message) == error.mlen);
    TEST_ASSERT_EQUAL_STRING_LEN(message, error.message, error.mlen);
}
int  main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ErrorAdd);
    UNITY_END();
}
