# Setup
- Clone
```sh
git clone https://github.com/hxero/curleave
cd curleave
```
- Build
```sh
meson setup build && ninja -C build
```
- Load the plugin
```sh
hyprctl plugin load $(pwd)/build/libcurleave.so
```
