#ifndef LUA_USB_OBJECTS_BOSDEVCAPABILITYDESCRIPTOR_H
#define LUA_USB_OBJECTS_BOSDEVCAPABILITYDESCRIPTOR_H

#include "common.hpp"

namespace luausb {
	class BosDevCapabilityDescriptor : public Object<libusb_bos_dev_capability_descriptor> {
	public:
		explicit BosDevCapabilityDescriptor(State * state) : Object<libusb_bos_dev_capability_descriptor>(state){
			LUTOK_PROPERTY("length", &BosDevCapabilityDescriptor::getLength, &BosDevCapabilityDescriptor::nullMethod);
			LUTOK_PROPERTY("descriptorType", &BosDevCapabilityDescriptor::getDescriptorType, &BosDevCapabilityDescriptor::nullMethod);
			LUTOK_PROPERTY("capabilityType", &BosDevCapabilityDescriptor::getDevCapabilityType, &BosDevCapabilityDescriptor::nullMethod);
			LUTOK_PROPERTY("data", &BosDevCapabilityDescriptor::getCapabilityData, &BosDevCapabilityDescriptor::nullMethod);

			LUTOK_METHOD("getUSB2ExtensionDescriptor", &BosDevCapabilityDescriptor::getUSB2ExtensionDescriptor);
			LUTOK_METHOD("getSSUSBDeviceCapabilityDescriptor", &BosDevCapabilityDescriptor::getSSUSBDeviceCapabilityDescriptor);
			LUTOK_METHOD("getContainerIDDescriptor", &BosDevCapabilityDescriptor::getContainerIDDescriptor);
		}

		libusb_bos_dev_capability_descriptor * constructor(State & state, bool & managed);

		void destructor(State & state, libusb_bos_dev_capability_descriptor * descriptor);
		
		int getLength(State & state, libusb_bos_dev_capability_descriptor * descriptor);
		int getDescriptorType(State & state, libusb_bos_dev_capability_descriptor * descriptor);
		int getDevCapabilityType(State & state, libusb_bos_dev_capability_descriptor * descriptor);
		int getCapabilityData(State & state, libusb_bos_dev_capability_descriptor * descriptor);

		int getUSB2ExtensionDescriptor(State & state, libusb_bos_dev_capability_descriptor * descriptor);
		int getSSUSBDeviceCapabilityDescriptor(State & state, libusb_bos_dev_capability_descriptor * descriptor);
		int getContainerIDDescriptor(State & state, libusb_bos_dev_capability_descriptor * descriptor);
	};
};

#endif	
