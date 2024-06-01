project('tlisp', 'c',
  version: '0.0.1',
  license: 'MIT')
inc = include_directories('include')
src_inc = include_directories('src/lib')

subdir('include')
subdir('src/lib')
subdir('src/lib/tests')

pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : tlisplib,
                 version : '0.0.1',
                 name : 'libtlisp',
                 filebase : 'tlisp',
                 description : 'A tiny lisp.')
