#include "core/errors.h"
#include "tlisp/errors.h"
#include "tlisp/types.h"
#include "unity.h"
#include "unity_internals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static error_array array ;
static FILE *handle ;
static tlisp_error *error ;
static const char *message = "unterminated string";
void setUp() {
    array = (error_array){NULL};
    handle = error_openstream(&array);
    error = NULL;
}
void tearDown() {
    if (error != NULL) {

        tlisp_error_free(error);
        free(array.errors);
    }
    fclose(handle);
}
#ifdef CMAKE_BUILD_TESTS
int errStream(void) {
#else
void testErrStream(void) {
#endif /* ifdef CMAKE_BUILD_TESTS */
    error_adderror(handle, TLISP_ERR_UNTERMITATED_STRING, message);
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, array.count, "wrong array count");
    error = &array.errors[0];
    TEST_ASSERT_EQUAL_INT_MESSAGE(TLISP_ERR_UNTERMITATED_STRING,error->code , "Wrong error code");
    int err_len = strlen(message);
    TEST_ASSERT_EQUAL_INT_MESSAGE(err_len, error->mlen, "Wrong error len");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE(message, error->message, error->mlen, "Wrong error message");
}
int main() {
    UNITY_BEGIN();
    RUN_TEST(testErrStream);
    UNITY_END();
}
