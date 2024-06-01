tlispruntime_sources = [
  'vm.h', 'vm.c',
  'opcode.h', 'opcode_strs.h' ]
tlispruntime = static_library('tlispruntime',
  tlispruntime_sources,
  dependencies: [tlispcore_dep, tlisparrays_dep],
  include_directories: config_inc)
tlispruntime_dep = declare_dependency(
  link_with: tlispruntime,
  dependencies: [tlispcore_dep, tlisparrays_dep],
  include_directories: config_inc)
