#ifndef LUA_USB_OBJECTS_SSENDPOINTCOMPANIONDESCRIPTOR_H
#define LUA_USB_OBJECTS_SSENDPOINTCOMPANIONDESCRIPTOR_H

#include "common.hpp"

namespace luausb {
	class SSEndpointCompanionDescriptor : public Object<libusb_ss_endpoint_companion_descriptor> {
	public:
		explicit SSEndpointCompanionDescriptor(State * state) : Object<libusb_ss_endpoint_companion_descriptor>(state){
			LUTOK_PROPERTY("length", &SSEndpointCompanionDescriptor::getLength, &SSEndpointCompanionDescriptor::nullMethod);
			LUTOK_PROPERTY("descriptorType", &SSEndpointCompanionDescriptor::getDescriptorType, &SSEndpointCompanionDescriptor::nullMethod);
			LUTOK_PROPERTY("maxBurst", &SSEndpointCompanionDescriptor::getMaxBurst, &SSEndpointCompanionDescriptor::nullMethod);
			LUTOK_PROPERTY("attributes", &SSEndpointCompanionDescriptor::getAttributes, &SSEndpointCompanionDescriptor::nullMethod);
			LUTOK_PROPERTY("bytesPerInterval", &SSEndpointCompanionDescriptor::getBytesPerInterval, &SSEndpointCompanionDescriptor::nullMethod);
		}

		libusb_ss_endpoint_companion_descriptor * constructor(State & state, bool & managed);

		void destructor(State & state, libusb_ss_endpoint_companion_descriptor * descriptor);

		int getLength(State & state, libusb_ss_endpoint_companion_descriptor * descriptor);
		int getDescriptorType(State & state, libusb_ss_endpoint_companion_descriptor * descriptor);
		int getMaxBurst(State & state, libusb_ss_endpoint_companion_descriptor * descriptor);
		int getAttributes(State & state, libusb_ss_endpoint_companion_descriptor * descriptor);
		int getBytesPerInterval(State & state, libusb_ss_endpoint_companion_descriptor * descriptor);
	};
};

#endif	
