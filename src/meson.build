

feat_build_tests = get_option('build_tests')\
    .enable_auto_if(get_option('buildtype') == 'debug')

feat_language_debug = get_option('language_debug')\
    .enable_auto_if(get_option('buildtype') == 'debug')

if feat_language_debug.enabled() 
  conf_data.set('LANG_DEBUG', true)
endif

 test_dep = feat_build_tests.enabled() ? \
     declare_dependency() : disabler()

subdir('lib')
subdir('bin')
