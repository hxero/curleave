# Setup
- Clone
```sh
git clone https://github.com/hxero/curleave
cd curleave
```
 \
- Build
```sh
meson setup build && -C build
```
 \
- Load the plugin
```sh
hyprctl plugin load build/libcurleave.so
```
