

feat_build_tests = get_option('build_tests')\
    .enable_auto_if(get_option('buildtype') == 'debug')

feat_language_debug = get_option('language_debug')\
    .enable_auto_if(get_option('buildtype') == 'debug')

if feat_language_debug.enabled() 
  conf_data.set('LANG_DEBUG', true)
endif

if feat_build_tests.enabled()
    unity_proj = subproject('unity')
    unity_dep = unity_proj.get_variable('unity_dep')
else
    unity_dep = disabler()
endif
subdir('lib')
subdir('bin')
