tlisp_sources = [ 'state.c', 'state.h',
                  'errors.c', 'errors.h',
                  'memory.c', 'memory.h',
                  'vm.h', 'vm.c',
                  'chunk.h', 'chunk.c',
                  'value.h', 'value.c',
                  'opcode.h', 'opcode_strs.h' ]
lib_inc = include_directories('.')
tlisplib = shared_library('tlisp',
                          tlisp_sources,
                          include_directories : [
                            inc, config_inc, lib_inc
                            ],
                          install : true)
