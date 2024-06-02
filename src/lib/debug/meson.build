feat_debug_trace = get_option('debug_trace_execution')\
    .enable_auto_if(feat_language_debug.enabled())

if feat_debug_trace.enabled() 
  conf_data.set('DEBUG_TRACE_EXECUTION', true)
endif

feat_debug_print = get_option('debug_print_code')\
    .enable_auto_if(feat_language_debug.enabled())

if feat_debug_print.enabled()
  conf_data.set('DEBUG_PRINT_CODE', true)
endif

tlispdebug_sources = ['debug.c', 'debug.h']
tlispdebug = static_library('tlispdebug',
  tlispdebug_sources,
  dependencies: tlisparrays_dep,
)
tlispdebug_dep = feat_language_debug.enabled()?\
    declare_dependency(
      link_with: tlispdebug,
      dependencies: tlisparrays_dep,
) : disabler()
