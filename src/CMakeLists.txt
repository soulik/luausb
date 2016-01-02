set(luausb_src
	main.cpp
	constants.cpp
)

set(luausb_h
	common.hpp
	init_classes.hpp
	constants.hpp
)

set(luausb_objects_src
	objects/BosDescriptor.cpp
	objects/BosDevCapabilityDescriptor.cpp
	objects/ConfigDescriptor.cpp
	objects/ContainerIDDescriptor.cpp
	objects/Context.cpp
	objects/ControlSetup.cpp
	objects/Device.cpp
	objects/DeviceHandle.cpp
	objects/DeviceDescriptor.cpp
	objects/EndpointDescriptor.cpp
	objects/ISOPacketDescriptor.cpp
	objects/Interface.cpp
	objects/InterfaceDescriptor.cpp
	objects/ContainerIDDescriptor.cpp
	objects/USB20ExtensionDescriptor.cpp
	objects/SSUSBDeviceCapabilityDescriptor.cpp
	objects/SSEndpointCompanionDescriptor.cpp
	objects/Transfer.cpp
)

set(luausb_objects_h
	objects/BosDescriptor.hpp
	objects/BosDevCapabilityDescriptor.hpp
	objects/ConfigDescriptor.hpp
	objects/ContainerIDDescriptor.hpp
	objects/Context.hpp
	objects/ControlSetup.hpp
	objects/Device.hpp
	objects/DeviceHandle.hpp
	objects/DeviceDescriptor.hpp
	objects/EndpointDescriptor.hpp
	objects/ISOPacketDescriptor.hpp
	objects/Interface.hpp
	objects/InterfaceDescriptor.hpp
	objects/ContainerIDDescriptor.hpp
	objects/USB20ExtensionDescriptor.hpp
	objects/SSUSBDeviceCapabilityDescriptor.hpp
	objects/SSEndpointCompanionDescriptor.hpp
	objects/Transfer.hpp
)

set(luausb_sources
	${luausb_src} ${luausb_h} ${luausb_objects_src} ${luausb_objects_h}
)

include_directories(./)

source_group("Header files" FILES ${luausb_h})
source_group(objects FILES ${luausb_objects_src} ${luausb_objects_h})

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

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

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
	libusb ${LUA_LIBRARY}
)

