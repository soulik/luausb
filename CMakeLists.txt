cmake_minimum_required (VERSION 3.1.0)
project (luausb)

# Include libusb

include_directories(dependencies/libusb/libusb)
add_subdirectory(dependencies/libusb)

# Include Lua 5.1

include(FindLua51)
include_directories(SYSTEM
	${LUA_INCLUDE_DIR}
	${LUA_INCLUDE_DIR}/lua5.1
)

include_directories(dependencies/lutok2/include)

add_subdirectory(src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
set_target_properties(luausb PROPERTIES PREFIX "")

