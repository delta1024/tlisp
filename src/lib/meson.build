subdir('core') 
subdir('arrays')
subdir('debug')
subdir('compiler')
subdir('runtime')
libtlisp_sources = [ 'state.c', 'state.h', 'errors.c' ]
lib_deps = [
    tlispcore_dep,
    tlisparrays_dep,
    tlispruntime_dep,
    tlispcompiler_dep,
]
if tlispdebug_dep.found() 
    lib_deps += tlispdebug_dep 
endif 
libtlisp = library('tlisp', 
    libtlisp_sources,
    dependencies : lib_deps, 
    install : true)

libtlisp_dep = declare_dependency(
    link_with : libtlisp, 
    include_directories : inc) 
subdir('tests', if_found: unity_dep)
