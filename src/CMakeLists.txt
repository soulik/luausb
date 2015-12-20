set(luausb_src
	main.cpp
)

set(luausb_h
	common.hpp
)

set(luausb_sources
	${luausb_src} ${luausb_h}
)

include_directories(./)

source_group("Header files" FILES ${luausb_h})

set(luausb_version_script luausb.version)

IF(UNIX)
    IF(CMAKE_COMPILER_IS_GNUCC)
         SET(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} ${CMAKE_CXX_COMPILE_OPTIONS_VISIBILITY}hidden -Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/${luausb_version_script}")
    ENDIF(CMAKE_COMPILER_IS_GNUCC)

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-declarations")
ENDIF(UNIX)

add_library(luausb SHARED
	${luausb_sources}
)

set_property(TARGET luausb PROPERTY CXX_STANDARD 11)
set_property(TARGET luausb PROPERTY CXX_STANDARD_REQUIRED ON)

set_target_properties(luausb
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_PROCESSOR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_PROCESSOR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_PROCESSOR}/bin"
)

configure_file(usb.lua ${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_PROCESSOR}/lib/usb.lua COPYONLY)

target_link_libraries (luausb
	${LUA_LIBRARY}
)

