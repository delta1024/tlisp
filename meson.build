project('tlisp', 'c',
  version: '0.0.1',
  license: 'MIT',
  default_options: 'c_std=gnu11'
)

conf_data = configuration_data()

config_inc = include_directories('.')
inc = include_directories('include')
feat_build_tests = get_option('build_tests')\
    .enable_auto_if(get_option('buildtype') == 'debug')

feat_language_debug = get_option('language_debug')\
    .enable_auto_if(get_option('buildtype') == 'debug')

if feat_language_debug.enabled() 
  conf_data.set('LANG_DEBUG', true)
endif

 test_dep = feat_build_tests.enabled() ? \
     declare_dependency() : disabler()

subdir('include')
subdir('src/lib')
subdir('src/bin')

configure_file( input : 'config.h.in',
                output: 'config.h',
                configuration: conf_data) 

pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : libtlisp,
                 version : '0.0.1',
                 name : 'libtlisp',
                 filebase : 'tlisp',
                 description : 'A tiny lisp.')
