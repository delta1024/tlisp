subdir('core')
subdir('arrays')
subdir('runtime')

libtlisp_sources = [ 'state.c', 'state.h', 'errors.c', ]

if feat_language_debug.enabled() 
  libtlisp_sources += [ 'debug.c', 'debug.h' ]
endif

feat_debug_trace = get_option('debug_trace_execution')\
    .enable_auto_if(feat_language_debug.enabled())

if feat_debug_trace.enabled() 
  conf_data.set('DEBUG_TRACE_EXECUTION', true)
endif

libtlisp = library('tlisp',
  libtlisp_sources,
  dependencies: [
    tlispcore_dep, 
    tlisparrays_dep, 
    tlispruntime_dep,
    ],
  install : true)

libtlisp_dep = declare_dependency(
  link_with: libtlisp, 
  include_directories: inc)
subdir('tests')
