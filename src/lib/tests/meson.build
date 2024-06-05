testerrstream = executable('testerrstream', 'errStream.c', 
  include_directories : [tlispcore_inc],
  dependencies: [unity_dep, libtlisp_dep])
test('errStream test', testerrstream)

testerradd = executable('testerradd', 'errAdd.c',
  dependencies: [unity_dep, libtlisp_dep])
test('errAdd test', testerradd)
