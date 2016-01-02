#include "objects/Transfer.hpp"
#include "objects/ControlSetup.hpp"
#include "objects/DeviceHandle.hpp"
#include "objects/ISOPacketDescriptor.hpp"

namespace luausb {
	libusb_transfer * Transfer::constructor(State & state, bool & managed){
		Stack * stack = state.stack;
		int ISOpackets = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			ISOpackets = stack->to<int>(1);
		}
		libusb_transfer * transfer = libusb_alloc_transfer(ISOpackets);
		return transfer;
	}

	void Transfer::destructor(State & state, libusb_transfer * transfer){
		libusb_free_transfer(transfer);
	}

	int Transfer::submit(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		int result = libusb_submit_transfer(transfer);
		if (result == 0){
			stack->push<bool>(true);
		}
		else{
			stack->push<int>(result);
		}
		return 1;
	}
	int Transfer::cancel(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		int result = libusb_cancel_transfer(transfer);
		if (result == 0){
			stack->push<bool>(true);
		}
		else{
			stack->push<int>(result);
		}
		return 1;
	}
	int Transfer::getStreamID(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		stack->push<LUA_NUMBER>(libusb_transfer_get_stream_id(transfer));
		return 1;
	}
	int Transfer::setStreamID(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			libusb_transfer_set_stream_id(transfer, static_cast<uint32_t>(stack->to<LUA_NUMBER>(1)));
		}
		return 0;
	}
	int Transfer::getControlSetup(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		ControlSetup * iControlSetup = OBJECT_IFACE(ControlSetup);
		libusb_control_setup * setup = libusb_control_transfer_get_setup(transfer);
		if (setup){
			iControlSetup->push(setup);
		}
		else{
			stack->pushNil();
		}
		return 1;
	}

	int Transfer::getDeviceHandle(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		DeviceHandle * iDeviceHandle = OBJECT_IFACE(DeviceHandle);
		iDeviceHandle->push(transfer->dev_handle);
		return 1;
	}
	int Transfer::getFlags(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		stack->push<int>(transfer->flags);
		return 1;
	}
	int Transfer::getEndpoint(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		stack->push<int>(transfer->endpoint);
		return 1;
	}
	int Transfer::getType(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		stack->push<int>(transfer->type);
		return 1;
	}
	int Transfer::getTimeout(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		stack->push<int>(transfer->timeout);
		return 1;
	}
	int Transfer::getStatus(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		stack->push<int>(transfer->status);
		return 1;
	}
	int Transfer::getLength(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		stack->push<int>(transfer->length);
		return 1;
	}
	int Transfer::getActualLength(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		stack->push<int>(transfer->actual_length);
		return 1;
	}
	int Transfer::getBuffer(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		const std::string buffer = std::string(reinterpret_cast<char*>(transfer->buffer), transfer->length);
		stack->pushLString(buffer, transfer->length);
		return 1;
	}
	int Transfer::getNumISOPackets(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		stack->push<int>(transfer->num_iso_packets);
		return 1;
	}
	int Transfer::getISOPackets(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		ISOPacketDescriptor * iISOPacketDesc = OBJECT_IFACE(ISOPacketDescriptor);

		stack->newTable();
		for (size_t i = 0; i < transfer->num_iso_packets; i++){
			stack->push<int>(i+1);
			iISOPacketDesc->push(&transfer->iso_packet_desc[i]);
			stack->setTable();
		}

		return 1;
	}

	void initTransfer(State * state, Module & module){
		INIT_OBJECT(Transfer);
	}
};
