testerrstream = executable('testerrstream', 'errStream.c', 'test_common.c',
  include_directories : [inc ,src_inc],
  link_with : tlisplib)
test('errStream test', testerrstream)

testerradd = executable('testerradd', 'errAdd.c', 'test_common.c',
  include_directories : [inc ,src_inc],
  link_with : tlisplib)
test('errAdd test', testerradd)
