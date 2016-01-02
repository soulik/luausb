#ifndef LUA_USB_OBJECTS_SSUSBDEVICECAPABILITYDESCRIPTOR_H
#define LUA_USB_OBJECTS_SSUSBDEVICECAPABILITYDESCRIPTOR_H

#include "common.hpp"

namespace luausb {
	class SSUSBDeviceCapabilityDescriptor : public Object<libusb_ss_usb_device_capability_descriptor> {
	public:
		explicit SSUSBDeviceCapabilityDescriptor(State * state) : Object<libusb_ss_usb_device_capability_descriptor>(state){
			LUTOK_PROPERTY("length", &SSUSBDeviceCapabilityDescriptor::getLength, &SSUSBDeviceCapabilityDescriptor::nullMethod);
			LUTOK_PROPERTY("descriptorType", &SSUSBDeviceCapabilityDescriptor::getDescriptorType, &SSUSBDeviceCapabilityDescriptor::nullMethod);
			LUTOK_PROPERTY("capabilityType", &SSUSBDeviceCapabilityDescriptor::getDevCapabilityType, &SSUSBDeviceCapabilityDescriptor::nullMethod);
			LUTOK_PROPERTY("attributes", &SSUSBDeviceCapabilityDescriptor::getAttributes, &SSUSBDeviceCapabilityDescriptor::nullMethod);
			LUTOK_PROPERTY("speedSupported", &SSUSBDeviceCapabilityDescriptor::getSpeedSupported, &SSUSBDeviceCapabilityDescriptor::nullMethod);
			LUTOK_PROPERTY("functionalitySupport", &SSUSBDeviceCapabilityDescriptor::getFunctionalitySupport, &SSUSBDeviceCapabilityDescriptor::nullMethod);
			LUTOK_PROPERTY("U1ExitLatency", &SSUSBDeviceCapabilityDescriptor::getU1ExitLatency, &SSUSBDeviceCapabilityDescriptor::nullMethod);
			LUTOK_PROPERTY("U2ExitLatency", &SSUSBDeviceCapabilityDescriptor::getU2ExitLatency, &SSUSBDeviceCapabilityDescriptor::nullMethod);
		}

		libusb_ss_usb_device_capability_descriptor * constructor(State & state, bool & managed);

		void destructor(State & state, libusb_ss_usb_device_capability_descriptor * descriptor);
		
		int getLength(State & state, libusb_ss_usb_device_capability_descriptor * descriptor);
		int getDescriptorType(State & state, libusb_ss_usb_device_capability_descriptor * descriptor);
		int getDevCapabilityType(State & state, libusb_ss_usb_device_capability_descriptor * descriptor);
		int getAttributes(State & state, libusb_ss_usb_device_capability_descriptor * descriptor);
		int getSpeedSupported(State & state, libusb_ss_usb_device_capability_descriptor * descriptor);
		int getFunctionalitySupport(State & state, libusb_ss_usb_device_capability_descriptor * descriptor);
		int getU1ExitLatency(State & state, libusb_ss_usb_device_capability_descriptor * descriptor);
		int getU2ExitLatency(State & state, libusb_ss_usb_device_capability_descriptor * descriptor);
	};
};

#endif	
