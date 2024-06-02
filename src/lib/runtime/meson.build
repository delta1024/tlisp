tlispruntime_sources = [
  'vm.h', 'vm.c',
  'stack.h', 'stack.c',
  'opcode.h', 'opcode_strs.h' ]
  run_deps = [tlispcore_dep, tlisparrays_dep]
if tlispdebug_dep.found() 
  run_deps += tlispdebug_dep
endif

tlispruntime = static_library('tlispruntime',
  tlispruntime_sources,
  dependencies: run_deps,
  include_directories: config_inc)

tlispruntime_dep = declare_dependency(
  link_with: tlispruntime,
  dependencies: run_deps,
  include_directories: config_inc)
