#ifndef LUA_USB_OBJECTS_TRANSFER_H
#define LUA_USB_OBJECTS_TRANSFER_H

#include "common.hpp"

namespace luausb {
	class Transfer : public Object<libusb_transfer> {
	public:
		explicit Transfer(State * state) : Object<libusb_transfer>(state){
			LUTOK_PROPERTY("streamID", &Transfer::getStreamID, &Transfer::setStreamID);
			LUTOK_PROPERTY("controlSetup", &Transfer::getControlSetup, &Transfer::nullMethod);

			LUTOK_METHOD("submit", &Transfer::submit);
			LUTOK_METHOD("cancel", &Transfer::cancel);

			LUTOK_PROPERTY("deviceHandle", &Transfer::getDeviceHandle, &Transfer::nullMethod);
			LUTOK_PROPERTY("flags", &Transfer::getFlags, &Transfer::nullMethod);
			LUTOK_PROPERTY("endpoint", &Transfer::getEndpoint, &Transfer::nullMethod);
			LUTOK_PROPERTY("type", &Transfer::getType, &Transfer::nullMethod);
			LUTOK_PROPERTY("timeout", &Transfer::getTimeout, &Transfer::nullMethod);
			LUTOK_PROPERTY("status", &Transfer::getStatus, &Transfer::nullMethod);
			LUTOK_PROPERTY("length", &Transfer::getLength, &Transfer::nullMethod);
			LUTOK_PROPERTY("actualLength", &Transfer::getActualLength, &Transfer::nullMethod);
			LUTOK_PROPERTY("buffer", &Transfer::getBuffer, &Transfer::nullMethod);
			LUTOK_PROPERTY("numISOPackets", &Transfer::getNumISOPackets, &Transfer::nullMethod);
			LUTOK_PROPERTY("ISOPackets", &Transfer::getISOPackets, &Transfer::nullMethod);
		}

		libusb_transfer * constructor(State & state, bool & managed);

		void destructor(State & state, libusb_transfer * transfer);

		int submit(State & state, libusb_transfer * transfer);
		int cancel(State & state, libusb_transfer * transfer);
		int getStreamID(State & state, libusb_transfer * transfer);
		int setStreamID(State & state, libusb_transfer * transfer);
		
		int getControlSetup(State & state, libusb_transfer * transfer);

		int getDeviceHandle(State & state, libusb_transfer * transfer);
		int getFlags(State & state, libusb_transfer * transfer);
		int getEndpoint(State & state, libusb_transfer * transfer);
		int getType(State & state, libusb_transfer * transfer);
		int getTimeout(State & state, libusb_transfer * transfer);
		int getStatus(State & state, libusb_transfer * transfer);
		int getLength(State & state, libusb_transfer * transfer);
		int getActualLength(State & state, libusb_transfer * transfer);
		int getBuffer(State & state, libusb_transfer * transfer);
		int getNumISOPackets(State & state, libusb_transfer * transfer);
		int getISOPackets(State & state, libusb_transfer * transfer);
	};
};

#endif	
