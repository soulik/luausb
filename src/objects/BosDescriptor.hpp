#ifndef LUA_USB_OBJECTS_BOSDESCRIPTOR_H
#define LUA_USB_OBJECTS_BOSDESCRIPTOR_H

#include "common.hpp"

namespace luausb {
	class BosDescriptor : public Object<libusb_bos_descriptor> {
	public:
		explicit BosDescriptor(State * state) : Object<libusb_bos_descriptor>(state){
			LUTOK_PROPERTY("length", &BosDescriptor::getLength, &BosDescriptor::nullMethod);
			LUTOK_PROPERTY("descriptorType", &BosDescriptor::getDescriptorType, &BosDescriptor::nullMethod);
			LUTOK_PROPERTY("totalLength", &BosDescriptor::getTotalLength, &BosDescriptor::nullMethod);
			LUTOK_PROPERTY("numDeviceCaps", &BosDescriptor::getNumDeviceCaps, &BosDescriptor::nullMethod);
			LUTOK_PROPERTY("capabilities", &BosDescriptor::getDeviceCapabilities, &BosDescriptor::nullMethod);
		}

		libusb_bos_descriptor * constructor(State & state, bool & managed);

		void destructor(State & state, libusb_bos_descriptor * descriptor);

		int getLength(State & state, libusb_bos_descriptor * descriptor);
		int getDescriptorType(State & state, libusb_bos_descriptor * descriptor);
		int getTotalLength(State & state, libusb_bos_descriptor * descriptor);
		int getNumDeviceCaps(State & state, libusb_bos_descriptor * descriptor);
		int getDeviceCapabilities(State & state, libusb_bos_descriptor * descriptor);
	};
};

#endif	
