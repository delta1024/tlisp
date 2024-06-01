#ifndef _TLISP_TEST_COMMON_H__
#define _TLISP_TEST_COMMON_H__

int _test_fail(const char *callee, const char *message, ...);
int _test_pass(const char *callee);
#define test_pass() _test_pass(__func__)
#define test_fail(...) _test_fail(__func__, __VA_ARGS__)

#endif // !_TLISP_TEST_COMMON_H__
