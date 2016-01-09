#ifndef LUA_USB_OBJECTS_TRANSFER_H
#define LUA_USB_OBJECTS_TRANSFER_H

#include "common.hpp"

namespace luausb {
	struct TransferData {
		State * state;
		int fnRef;
	};

	class Transfer : public Object<libusb_transfer> {
	public:
		explicit Transfer(State * state) : Object<libusb_transfer>(state){
			LUTOK_PROPERTY("streamID", &Transfer::getStreamID, &Transfer::setStreamID);
			LUTOK_PROPERTY("controlTransferData", &Transfer::getControlTransferData, &Transfer::setControlTransferData);
			LUTOK_PROPERTY("controlSetup", &Transfer::getControlSetup, &Transfer::nullMethod);

			LUTOK_METHOD("submit", &Transfer::submit);
			LUTOK_METHOD("cancel", &Transfer::cancel);

			LUTOK_PROPERTY("deviceHandle", &Transfer::getDeviceHandle, &Transfer::nullMethod);
			LUTOK_PROPERTY("flags", &Transfer::getFlags, &Transfer::setFlags);
			LUTOK_PROPERTY("endpoint", &Transfer::getEndpoint, &Transfer::setEndpoint);
			LUTOK_PROPERTY("type", &Transfer::getType, &Transfer::setType);
			LUTOK_PROPERTY("timeout", &Transfer::getTimeout, &Transfer::setTimeout);
			LUTOK_PROPERTY("status", &Transfer::getStatus, &Transfer::nullMethod);
			LUTOK_PROPERTY("length", &Transfer::getLength, &Transfer::setLength);
			LUTOK_PROPERTY("actualLength", &Transfer::getActualLength, &Transfer::nullMethod);
			LUTOK_PROPERTY("buffer", &Transfer::getBuffer, &Transfer::setBuffer);
			LUTOK_PROPERTY("numISOPackets", &Transfer::getNumISOPackets, &Transfer::nullMethod);
			LUTOK_PROPERTY("ISOPackets", &Transfer::getISOPackets, &Transfer::nullMethod);

			LUTOK_METHOD("fillControlSetup", &Transfer::fillControlSetup);
			LUTOK_METHOD("fillControlTransfer", &Transfer::fillControlTransfer);
			LUTOK_METHOD("fillControlTransferBuffer", &Transfer::fillControlTransferBuffer);
			LUTOK_METHOD("fillBulkTransfer", &Transfer::fillBulkTransfer);
			LUTOK_METHOD("fillBulkStreamTransfer", &Transfer::fillBulkStreamTransfer);
			LUTOK_METHOD("fillInterruptTransfer", &Transfer::fillInterruptTransfer);
			LUTOK_METHOD("fillISOTransfer", &Transfer::fillISOTransfer);
		}

		libusb_transfer * constructor(State & state, bool & managed);

		void destructor(State & state, libusb_transfer * transfer);

		int submit(State & state, libusb_transfer * transfer);
		int cancel(State & state, libusb_transfer * transfer);
		int getStreamID(State & state, libusb_transfer * transfer);
		int setStreamID(State & state, libusb_transfer * transfer);
		
		int getControlSetup(State & state, libusb_transfer * transfer);
		int getControlTransferData(State & state, libusb_transfer * transfer);
		int setControlTransferData(State & state, libusb_transfer * transfer);

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

		int setFlags(State & state, libusb_transfer * transfer);
		int setEndpoint(State & state, libusb_transfer * transfer);
		int setType(State & state, libusb_transfer * transfer);
		int setTimeout(State & state, libusb_transfer * transfer);
		int setLength(State & state, libusb_transfer * transfer);
		int setBuffer(State & state, libusb_transfer * transfer);

		int fillControlSetup(State & state, libusb_transfer * transfer);
		int fillControlTransfer(State & state, libusb_transfer * transfer);
		int fillControlTransferBuffer(State & state, libusb_transfer * transfer);
		int fillBulkTransfer(State & state, libusb_transfer * transfer);
		int fillBulkStreamTransfer(State & state, libusb_transfer * transfer);
		int fillInterruptTransfer(State & state, libusb_transfer * transfer);
		int fillISOTransfer(State & state, libusb_transfer * transfer);

		static void transferCallback(libusb_transfer *transfer);

		void setTransferCallback(State & state, libusb_transfer * transfer, int index);
		void freeTransferData(State & state, libusb_transfer * transfer);
		void reallocBuffer(State & state, libusb_transfer * transfer, size_t newLength, bool keepOldContent = false);
	};
};

#endif	
