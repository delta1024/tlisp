tlispcompiler_sources = []
tlispcompiler_deps = [
    tlispcore_dep,
    tlisparrays_dep,
    ]
if tlispdebug_dep.found()
    tlispcompiler_deps += tlispdebug_dep
endif
tlispcompiler = static_library(
    'tlispcompiler',
    tlispcompiler_sources,
    dependencies: tlispcompiler_deps)
tlispcompiler_dep = declare_dependency(
    link_with: tlispcompiler,
    dependencies: tlispcompiler_deps)
