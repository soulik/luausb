#ifndef LUA_USB_OBJECTS_USB20EXTENSIONDESCRIPTOR_H
#define LUA_USB_OBJECTS_USB20EXTENSIONDESCRIPTOR_H

#include "common.hpp"

namespace luausb {
	class USB20ExtensionDescriptor : public Object<libusb_usb_2_0_extension_descriptor> {
	public:
		explicit USB20ExtensionDescriptor(State * state) : Object<libusb_usb_2_0_extension_descriptor>(state){
			LUTOK_PROPERTY("length", &USB20ExtensionDescriptor::getLength, &USB20ExtensionDescriptor::nullMethod);
			LUTOK_PROPERTY("descriptorType", &USB20ExtensionDescriptor::getDescriptorType, &USB20ExtensionDescriptor::nullMethod);
			LUTOK_PROPERTY("capabilityType", &USB20ExtensionDescriptor::getDevCapabilityType, &USB20ExtensionDescriptor::nullMethod);
			LUTOK_PROPERTY("attributes", &USB20ExtensionDescriptor::getAttributes, &USB20ExtensionDescriptor::nullMethod);
		}

		libusb_usb_2_0_extension_descriptor * constructor(State & state, bool & managed);

		void destructor(State & state, libusb_usb_2_0_extension_descriptor * descriptor);

		int getLength(State & state, libusb_usb_2_0_extension_descriptor * descriptor);
		int getDescriptorType(State & state, libusb_usb_2_0_extension_descriptor * descriptor);
		int getDevCapabilityType(State & state, libusb_usb_2_0_extension_descriptor * descriptor);
		int getAttributes(State & state, libusb_usb_2_0_extension_descriptor * descriptor);
	};
};

#endif	
