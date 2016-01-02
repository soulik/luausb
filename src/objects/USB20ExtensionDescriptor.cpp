#include "objects/USB20ExtensionDescriptor.hpp"

namespace luausb {
	libusb_usb_2_0_extension_descriptor * USB20ExtensionDescriptor::constructor(State & state, bool & managed){
		return nullptr;
	}

	void USB20ExtensionDescriptor::destructor(State & state, libusb_usb_2_0_extension_descriptor * descriptor){
		libusb_free_usb_2_0_extension_descriptor(descriptor);
	}

	int USB20ExtensionDescriptor::getLength(State & state, libusb_usb_2_0_extension_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bLength);
		return 1;
	}

	int USB20ExtensionDescriptor::getDescriptorType(State & state, libusb_usb_2_0_extension_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bDescriptorType);
		return 1;
	}

	int USB20ExtensionDescriptor::getDevCapabilityType(State & state, libusb_usb_2_0_extension_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bDevCapabilityType);
		return 1;
	}

	int USB20ExtensionDescriptor::getAttributes(State & state, libusb_usb_2_0_extension_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bmAttributes);
		return 1;
	}

	void initUSB20ExtensionDescriptor(State * state, Module & module){
		INIT_OBJECT(USB20ExtensionDescriptor);
	}
};
