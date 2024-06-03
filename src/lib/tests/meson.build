testerrstream = executable('testerrstream', 'errStream.c', 'test_common.c',
  include_directories : [tlispcore_inc],
  dependencies: [test_dep, libtlisp_dep])
test('errStream test', testerrstream, protocol: 'tap')

testerradd = executable('testerradd', 'errAdd.c', 'test_common.c',
  dependencies: [test_dep, libtlisp_dep])
test('errAdd test', testerradd, protocol: 'tap')
