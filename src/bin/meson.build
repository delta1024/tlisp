build_repl_dep = get_option('build_repl_binary').enabled() ?\
    declare_dependency(
      dependencies: libtlisp_dep,
      ) : disabler()
tlisp_sources = ['main.c']
tlisp = executable('tlisp',
  tlisp_sources,
  dependencies: build_repl_dep,
  install: true)
run_target('repl', command: tlisp)
