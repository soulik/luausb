#ifndef LUA_USB_OBJECTS_INTERFACEDESCRIPTOR_H
#define LUA_USB_OBJECTS_INTERFACEDESCRIPTOR_H

#include "common.hpp"

namespace luausb {
	class InterfaceDescriptor : public Object<libusb_interface_descriptor> {
	public:
		explicit InterfaceDescriptor(State * state) : Object<libusb_interface_descriptor>(state){
			LUTOK_PROPERTY("length", &InterfaceDescriptor::getLength, &InterfaceDescriptor::nullMethod);
			LUTOK_PROPERTY("descriptorType", &InterfaceDescriptor::getDescriptorType, &InterfaceDescriptor::nullMethod);
			LUTOK_PROPERTY("interfaceNumber", &InterfaceDescriptor::getInterfaceNumber, &InterfaceDescriptor::nullMethod);
			LUTOK_PROPERTY("alternateSetting", &InterfaceDescriptor::getAlternateSetting, &InterfaceDescriptor::nullMethod);
			LUTOK_PROPERTY("numEndpoint", &InterfaceDescriptor::getNumEndpoint, &InterfaceDescriptor::nullMethod);
			LUTOK_PROPERTY("interfaceClass", &InterfaceDescriptor::getInterfaceClass, &InterfaceDescriptor::nullMethod);
			LUTOK_PROPERTY("interfaceSubClass", &InterfaceDescriptor::getInterfaceSubClass, &InterfaceDescriptor::nullMethod);
			LUTOK_PROPERTY("interfaceProtocol", &InterfaceDescriptor::getInterfaceProtocol, &InterfaceDescriptor::nullMethod);
			LUTOK_PROPERTY("interface", &InterfaceDescriptor::getInterface, &InterfaceDescriptor::nullMethod);
			LUTOK_PROPERTY("endpoints", &InterfaceDescriptor::getEndpoints, &InterfaceDescriptor::nullMethod);
			LUTOK_PROPERTY("extra", &InterfaceDescriptor::getExtra, &InterfaceDescriptor::nullMethod);
		}

		libusb_interface_descriptor * constructor(State & state, bool & managed);

		void destructor(State & state, libusb_interface_descriptor * descriptor);

		int getLength(State & state, libusb_interface_descriptor * descriptor);
		int getDescriptorType(State & state, libusb_interface_descriptor * descriptor);
		int getInterfaceNumber(State & state, libusb_interface_descriptor * descriptor);
		int getAlternateSetting(State & state, libusb_interface_descriptor * descriptor);
		int getNumEndpoint(State & state, libusb_interface_descriptor * descriptor);
		int getInterfaceClass(State & state, libusb_interface_descriptor * descriptor);
		int getInterfaceSubClass(State & state, libusb_interface_descriptor * descriptor);
		int getInterfaceProtocol(State & state, libusb_interface_descriptor * descriptor);
		int getInterface(State & state, libusb_interface_descriptor * descriptor);
		int getEndpoints(State & state, libusb_interface_descriptor * descriptor);
		int getExtra(State & state, libusb_interface_descriptor * descriptor);
	};
};

#endif	
