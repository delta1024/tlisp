project('tlisp', 'c',
  version: '0.0.1',
  license: 'MIT')

inc = include_directories('include')

if get_option('build_tests').enabled()
  src_inc = include_directories('src/lib')
else
  src_inc = disabler()
endif

conf_data = configuration_data()
conf_data.set('uint8_max', 256)
configure_file( input : 'config.h.in',
                output: 'config.h',
                configuration: conf_data) 
config_inc = include_directories('.')

subdir('include')
subdir('src/lib')
subdir('src/lib/tests')

pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : tlisplib,
                 version : '0.0.1',
                 name : 'libtlisp',
                 filebase : 'tlisp',
                 description : 'A tiny lisp.')
