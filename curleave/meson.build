project('curleave', 'cpp',
  version: '1.0',
  default_options: ['buildtype=release'],
)

cpp_compiler = meson.get_compiler('cpp')
if cpp_compiler.has_argument('-std=c++23')
  add_global_arguments('-std=c++23', language: 'cpp')
elif cpp_compiler.has_argument('-std=c++2b')
  add_global_arguments('-std=c++2b', language: 'cpp')
else
  error('Compiler does not support C++23')
endif

shared_module('curleave', 'curleave.cpp',
  dependencies: [
    dependency('hyprland'),
    dependency('pixman-1'),
    dependency('libdrm'),
    dependency('libinput'),
    dependency('libudev'),
    dependency('wayland-server'),
    dependency('xkbcommon'),
  ],
  install: true,
)
