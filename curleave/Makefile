# Else exist specifically for clang
ifeq ($(CXX),g++)
    EXTRA_FLAGS = --no-gnu-unique
else
    EXTRA_FLAGS =
endif

CXXFLAGS ?= -O2
CXXFLAGS += -shared -fPIC -std=c++23

all:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(EXTRA_FLAGS) curleave.cpp -o curleave.so `pkg-config --cflags pixman-1 libdrm libinput libudev hyprland wayland-server xkbcommon`

clean:
	rm ./curleave.so

meson-build:
	mkdir -p build
	cd build && meson .. && ninja

.PHONY: all meson-build clean
