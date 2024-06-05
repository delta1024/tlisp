!#/usr/bin/env bash
meson compile -C build
./build/src/bin/tlisp $@
