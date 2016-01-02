#ifndef LUA_USB_OBJECTS_ISOPACKETDESCRIPTOR_H
#define LUA_USB_OBJECTS_ISOPACKETDESCRIPTOR_H

#include "common.hpp"

namespace luausb {
	class ISOPacketDescriptor : public Object<libusb_iso_packet_descriptor> {
	public:
		explicit ISOPacketDescriptor(State * state) : Object<libusb_iso_packet_descriptor>(state){
			LUTOK_PROPERTY("length", &ISOPacketDescriptor::getLength, &ISOPacketDescriptor::nullMethod);
			LUTOK_PROPERTY("actualLength", &ISOPacketDescriptor::getActualLength, &ISOPacketDescriptor::nullMethod);
			LUTOK_PROPERTY("status", &ISOPacketDescriptor::getStatus, &ISOPacketDescriptor::nullMethod);
		}

		libusb_iso_packet_descriptor * constructor(State & state, bool & managed);

		void destructor(State & state, libusb_iso_packet_descriptor * descriptor);

		int getLength(State & state, libusb_iso_packet_descriptor * descriptor);
		int getActualLength(State & state, libusb_iso_packet_descriptor * descriptor);
		int getStatus(State & state, libusb_iso_packet_descriptor * descriptor);
	};
};

#endif	
