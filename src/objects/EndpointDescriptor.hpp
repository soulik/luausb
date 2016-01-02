#ifndef LUA_USB_OBJECTS_ENDPOINTDESCRIPTOR_H
#define LUA_USB_OBJECTS_ENDPOINTDESCRIPTOR_H

#include "common.hpp"

namespace luausb {
	class EndpointDescriptor : public Object<libusb_endpoint_descriptor> {
	public:
		explicit EndpointDescriptor(State * state) : Object<libusb_endpoint_descriptor>(state){
			LUTOK_PROPERTY("length", &EndpointDescriptor::getLength, &EndpointDescriptor::nullMethod);
			LUTOK_PROPERTY("descriptorType", &EndpointDescriptor::getDescriptorType, &EndpointDescriptor::nullMethod);
			LUTOK_PROPERTY("endpointAddress", &EndpointDescriptor::getEndpointAddress, &EndpointDescriptor::nullMethod);
			LUTOK_PROPERTY("attributes", &EndpointDescriptor::getAttributes, &EndpointDescriptor::nullMethod);
			LUTOK_PROPERTY("maxPacketSize", &EndpointDescriptor::getMaxPacketSize, &EndpointDescriptor::nullMethod);
			LUTOK_PROPERTY("interval", &EndpointDescriptor::getInterval, &EndpointDescriptor::nullMethod);
			LUTOK_PROPERTY("refresh", &EndpointDescriptor::getRefresh, &EndpointDescriptor::nullMethod);
			LUTOK_PROPERTY("synchAddress", &EndpointDescriptor::getSynchAddress, &EndpointDescriptor::nullMethod);
			LUTOK_PROPERTY("extra", &EndpointDescriptor::getExtra, &EndpointDescriptor::nullMethod);
			LUTOK_PROPERTY("SSCompanionDescriptor", &EndpointDescriptor::getSSCompanionDescriptor, &EndpointDescriptor::nullMethod);
		}

		libusb_endpoint_descriptor * constructor(State & state, bool & managed);

		void destructor(State & state, libusb_endpoint_descriptor * descriptor);

		int getLength(State & state, libusb_endpoint_descriptor * descriptor);
		int getDescriptorType(State & state, libusb_endpoint_descriptor * descriptor);
		int getEndpointAddress(State & state, libusb_endpoint_descriptor * descriptor);
		int getAttributes(State & state, libusb_endpoint_descriptor * descriptor);
		int getMaxPacketSize(State & state, libusb_endpoint_descriptor * descriptor);
		int getInterval(State & state, libusb_endpoint_descriptor * descriptor);
		int getRefresh(State & state, libusb_endpoint_descriptor * descriptor);
		int getSynchAddress(State & state, libusb_endpoint_descriptor * descriptor);
		int getExtra(State & state, libusb_endpoint_descriptor * descriptor);
		int getSSCompanionDescriptor(State & state, libusb_endpoint_descriptor * descriptor);
	};
};

#endif	
