tlispcore_sources = ['errors.h', 'errors.c',
                     'memory.h', 'memory.c']
tlispcore = static_library('tlispcore', 
                            tlispcore_sources,
                            include_directories: inc,
) 

tlispcore_inc = [ include_directories('..'), inc ]
tlispcore_dep = declare_dependency(link_with: tlispcore,
                            include_directories: tlispcore_inc)
