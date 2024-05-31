#include "tlisp/types.h"
#include "unity.h"
#include "errors.h"
#include "unity_internals.h"
#include <stdio.h>
void setUp(void) {}
void tearDown(void){}
void test_errstream(void) {
error_array array = {0,0,0,NULL};
    FILE *handle = error_openstream(&array);
    error_adderror(handle, TLISP_ERR_UNTERMITATED_STRING, "unterminated string");

    TEST_ASSERT_MESSAGE(array.count == 1, "Error array wrong size.");
    tlisp_error *err = &array.errors[0];
    TEST_ASSERT(err->code == TLISP_ERR_UNTERMITATED_STRING);
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("unterminated string", err->message, err->mlen, "err strings not equal");
        
}
int main() {
    UNITY_BEGIN();
    RUN_TEST(test_errstream);
    UNITY_END();
}
