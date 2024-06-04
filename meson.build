project('tlisp', 'c',
  version: '0.0.1',
  license: 'MIT',
  default_options: 'c_std=gnu11'
)

conf_data = configuration_data()

config_inc = include_directories('.')
inc = include_directories('include')

subdir('include')
subdir('src')

configure_file( input : 'config.h.in',
                output: 'config.h',
                configuration: conf_data) 

pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : libtlisp,
                 version : '0.0.1',
                 name : 'libtlisp',
                 filebase : 'tlisp',
                 description : 'A tiny lisp.')
