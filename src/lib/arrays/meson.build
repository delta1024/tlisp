tlisparrays_sources = [
  'chunk.c', 'chunk.h',
  'value.c', 'value.h',
  ]

tlisparrays = static_library('tlisparrays',
  tlisparrays_sources,
  dependencies: tlispcore_dep)

tlisparrays_dep = declare_dependency(
  link_with: tlisparrays,
  dependencies: tlispcore_dep)
