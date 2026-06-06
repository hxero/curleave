project('curleave', 'cpp',
  version: '1.0',
  default_options: ['buildtype=release'],
)

cpp_compiler = meson.get_compiler('cpp')
if cpp_compiler.has_argument('-std=c++26')
  add_global_arguments('-std=c++26', language: 'cpp')
elif cpp_compiler.has_argument('-std=c++23')
  add_global_arguments('-std=c++23', language: 'cpp')
else
  error('Compiler does not support C++23 or C++26')
endif

shared_module('curleave', 'curleave.cpp',
  dependencies: [
    dependency('hyprland'),
    dependency('wayland-server'),
    dependency('xkbcommon'),
  ],
  install: true,
)
