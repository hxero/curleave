# Setup (Hyprpm)
Update headers
```sh
hyprpm update
```
Add repository
```sh
hyprpm add https://github.com/hxero/hyplugs
```
Enable a plugin!
```sh
hyprpm enable curleave
```

# Setup (Manual)
Clone repository
```sh
git clone https://github.com/hxero/hyplugs
cd hyplugs
```
Build a plugin
```sh
make -C curleave all
```
Load the plugin
```sh
hyprctl plugin load $(pwd)/curleave/curleave.so
```
