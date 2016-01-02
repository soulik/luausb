#include "objects/ISOPacketDescriptor.hpp"

namespace luausb {
	libusb_iso_packet_descriptor * ISOPacketDescriptor::constructor(State & state, bool & managed){
		return nullptr;
	}

	void ISOPacketDescriptor::destructor(State & state, libusb_iso_packet_descriptor * descriptor){
		delete descriptor;
	}

	int ISOPacketDescriptor::getLength(State & state, libusb_iso_packet_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->length);
		return 1;
	}
	int ISOPacketDescriptor::getActualLength(State & state, libusb_iso_packet_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->actual_length);
		return 1;
	}
	int ISOPacketDescriptor::getStatus(State & state, libusb_iso_packet_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->status);
		return 1;
	}

	void initISOPacketDescriptor(State * state, Module & module){
		INIT_OBJECT(ISOPacketDescriptor);
	}
};
