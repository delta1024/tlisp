tlispcore_sources = ['errors.h', 'errors.c',
                     'memory.h', 'memory.c',
                     'stack.h', 'stack.c',
                     'value.h', 'value.c']
tlispcore = static_library('tlispcore', 
                            tlispcore_sources,
                            include_directories: [inc,config_inc],
) 

tlispcore_inc = [ include_directories('..'), inc, config_inc ]
tlispcore_dep = declare_dependency(link_with: tlispcore,
                            include_directories: tlispcore_inc)
