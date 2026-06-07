cmake_minimum_required(VERSION 3.27)
project(curleave
	DESCRIPTION "A hyprland plugin to unfocus windows when the cursor leave it"
	VERSION 1.0
)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SRC "*.cpp")

add_library(curleave SHARED ${SRC})

find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET
	libdrm
	libinput
	libudev
	pixman-1
	hyprland
	wayland-server
	xkbcommon
)
target_link_libraries(curleave PRIVATE rt PkgConfig::deps)

install(TARGET curleave)
