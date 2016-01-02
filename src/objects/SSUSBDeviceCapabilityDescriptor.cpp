#include "objects/SSUSBDeviceCapabilityDescriptor.hpp"

namespace luausb {
	libusb_ss_usb_device_capability_descriptor * SSUSBDeviceCapabilityDescriptor::constructor(State & state, bool & managed){
		return nullptr;
	}

	void SSUSBDeviceCapabilityDescriptor::destructor(State & state, libusb_ss_usb_device_capability_descriptor * descriptor){
		libusb_free_ss_usb_device_capability_descriptor(descriptor);
	}

	int SSUSBDeviceCapabilityDescriptor::getLength(State & state, libusb_ss_usb_device_capability_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bLength);
		return 1;
	}

	int SSUSBDeviceCapabilityDescriptor::getDescriptorType(State & state, libusb_ss_usb_device_capability_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bDescriptorType);
		return 1;
	}

	int SSUSBDeviceCapabilityDescriptor::getDevCapabilityType(State & state, libusb_ss_usb_device_capability_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bDevCapabilityType);
		return 1;
	}

	int SSUSBDeviceCapabilityDescriptor::getAttributes(State & state, libusb_ss_usb_device_capability_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bmAttributes);
		return 1;
	}

	int SSUSBDeviceCapabilityDescriptor::getSpeedSupported(State & state, libusb_ss_usb_device_capability_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->wSpeedSupported);
		return 1;
	}

	int SSUSBDeviceCapabilityDescriptor::getFunctionalitySupport(State & state, libusb_ss_usb_device_capability_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bFunctionalitySupport);
		return 1;
	}

	int SSUSBDeviceCapabilityDescriptor::getU1ExitLatency(State & state, libusb_ss_usb_device_capability_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bU1DevExitLat);
		return 1;
	}

	int SSUSBDeviceCapabilityDescriptor::getU2ExitLatency(State & state, libusb_ss_usb_device_capability_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bU2DevExitLat);
		return 1;
	}

	void initSSUSBDeviceCapabilityDescriptor(State * state, Module & module){
		INIT_OBJECT(SSUSBDeviceCapabilityDescriptor);
	}
};
