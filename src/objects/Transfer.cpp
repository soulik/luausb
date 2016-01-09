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
		transfer->user_data = nullptr;
		transfer->buffer = nullptr;
		transfer->length = 0;
		transfer->actual_length = 0;
		return transfer;
	}

	void Transfer::freeTransferData(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		if (transfer->user_data){
			TransferData * data = static_cast<TransferData *>(transfer->user_data);
			if (data->fnRef != LUA_REFNIL){
				stack->unref(data->fnRef);
			}
			data->fnRef = LUA_REFNIL;
			delete data;
			transfer->user_data = nullptr;
		}
	}

	void Transfer::setTransferCallback(State & state, libusb_transfer * transfer, int index){
		Stack * stack = state.stack;
		freeTransferData(state, transfer);
		TransferData * transferData = new TransferData;
		transferData->state = &state;
		stack->pushValue(index);
		transferData->fnRef = stack->ref();
		transfer->user_data = transferData;
	}

	void Transfer::destructor(State & state, libusb_transfer * transfer){
		freeTransferData(state, transfer);
		if (transfer->buffer && !(transfer->flags & LIBUSB_TRANSFER_FREE_BUFFER)){
			delete[] transfer->buffer;
		}
		if (!(transfer->flags & LIBUSB_TRANSFER_FREE_TRANSFER)){
			libusb_free_transfer(transfer);
		}
	}

	int Transfer::submit(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		int result = libusb_submit_transfer(transfer);
		if (result == LIBUSB_SUCCESS){
			stack->push<bool>(true);
			return 1;
		}
		else{
			stack->push<bool>(false);
			stack->push<int>(result);
			return 2;
		}
	}
	int Transfer::cancel(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		int result = libusb_cancel_transfer(transfer);
		if (result == LIBUSB_SUCCESS){
			stack->push<bool>(true);
			return 1;
		}
		else{
			stack->push<bool>(false);
			stack->push<int>(result);
			return 2;
		}
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

	int Transfer::setFlags(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			transfer->flags = stack->to<int>(1);
		}
		return 0;
	}
	int Transfer::setEndpoint(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			transfer->endpoint = stack->to<int>(1);
		}
		return 0;
	}
	int Transfer::setType(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			transfer->type = stack->to<int>(1);
		}
		return 0;
	}
	int Transfer::setTimeout(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			transfer->timeout = stack->to<int>(1);
		}
		return 0;
	}
	void Transfer::reallocBuffer(State & state, libusb_transfer * transfer, size_t newLength, bool keepOldContent){
		Stack * stack = state.stack;
		if (newLength != transfer->length){
			unsigned char * newBuffer = new unsigned char[newLength];
			if (keepOldContent && newLength>0){
				memcpy(newBuffer, transfer->buffer, (transfer->length < newLength) ? transfer->length : newLength);
			}
			if (transfer->buffer){
				delete[] transfer->buffer;
			}
			transfer->buffer = newBuffer;
			transfer->length = newLength;
		}
	}
	int Transfer::setLength(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			reallocBuffer(state, transfer, stack->to<int>(1), true);
		}
		return 0;
	}
	int Transfer::setBuffer(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1)){
			const std::string data = stack->toLString(1);
			int newLength = data.length();
			reallocBuffer(state, transfer, newLength, false);
			memcpy(transfer->buffer, data.c_str(), newLength);
		}
		return 0;
	}

	/*
		fillControlSetup(requestType, request, value, index, length, data)
	*/
	int Transfer::fillControlSetup(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TNUMBER>(2) && stack->is<LUA_TNUMBER>(3) && stack->is<LUA_TNUMBER>(4) && stack->is<LUA_TNUMBER>(5)){
			uint16_t length = stack->to<int>(5);
			uint16_t bufferLength = LIBUSB_CONTROL_SETUP_SIZE + length;
			unsigned char * buffer = new unsigned char[bufferLength];
			
			if (stack->is<LUA_TSTRING>(6)){
				const std::string data = stack->toLString(6);
				size_t dataLength = data.length();
				memcpy(buffer + LIBUSB_CONTROL_SETUP_SIZE, data.c_str(), (dataLength > length) ? length : dataLength);
			}

			libusb_fill_control_setup(buffer, stack->to<int>(1), stack->to<int>(2), stack->to<int>(3), stack->to<int>(4), length);
			stack->pushLString(reinterpret_cast<char*>(buffer), bufferLength);
			delete[] buffer;
			return 1;
		}
		return 0;
	}

	int Transfer::fillControlTransferBuffer(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TSTRING>(2)){
			const std::string buffer = stack->toLString(1);
			const std::string data = stack->toLString(2);
			size_t bufferLength = buffer.length();
			size_t dataLength = data.length();

			struct libusb_control_setup *setup = (struct libusb_control_setup *)(void *)buffer.c_str();
			uint16_t maxLength = libusb_le16_to_cpu(setup->wLength);

			char * out = new char[bufferLength];
			memcpy(out, buffer.c_str(), LIBUSB_CONTROL_SETUP_SIZE);
			memcpy(out + LIBUSB_CONTROL_SETUP_SIZE, data.c_str(), (dataLength > maxLength) ? maxLength : dataLength);
			stack->pushLString(out, bufferLength);
			delete[] out;
			return 1;
		}
		return 0;
	}

	/*
		fillControlTransfer(devHandle, buffer, callback_fn, timeout)
	*/
	int Transfer::fillControlTransfer(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		DeviceHandle * iDeviceHandle = OBJECT_IFACE(DeviceHandle);
		libusb_device_handle * devHandle = iDeviceHandle->get(1);
		if (devHandle && stack->is<LUA_TFUNCTION>(3)){
			unsigned int timeout = 0;
			unsigned char * newBuffer = nullptr;

			setTransferCallback(state, transfer, 3);
			if (stack->is<LUA_TNUMBER>(4)){
				timeout = stack->to<int>(4);
			}

			if (stack->is<LUA_TSTRING>(2)){
				std::string buffer = stack->toLString(2);
				reallocBuffer(state, transfer, buffer.length());
				memcpy(transfer->buffer, buffer.c_str(), buffer.length());
				newBuffer = transfer->buffer;
			}

			libusb_fill_control_transfer(transfer, devHandle, newBuffer, &this->transferCallback, transfer->user_data, timeout);
		}
		return 0;
	}
	
	/*
		fillBulkTransfer(devHandle, endpoint, buffer, length, callback_fn, timeout)
	*/
	int Transfer::fillBulkTransfer(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		DeviceHandle * iDeviceHandle = OBJECT_IFACE(DeviceHandle);
		libusb_device_handle * devHandle = iDeviceHandle->get(1);
		if (devHandle && stack->is<LUA_TNUMBER>(2) && stack->is<LUA_TFUNCTION>(5)){
			unsigned int timeout = 0;
			unsigned char * newBuffer = nullptr;
			int length = 0;
			char endpoint = stack->to<int>(2);

			if (stack->is<LUA_TNUMBER>(4)){
				length = stack->to<int>(4);
			}

			setTransferCallback(state, transfer, 5);
			if (stack->is<LUA_TNUMBER>(6)){
				timeout = stack->to<int>(6);
			}

			if (stack->is<LUA_TSTRING>(3)){
				std::string buffer = stack->toLString(3);
				size_t bufferLength = buffer.length();
				size_t bufferSizeToCopy = bufferLength;
				if (length == 0){
					length = bufferLength;
				}
				reallocBuffer(state, transfer, length);
				memcpy(transfer->buffer, buffer.c_str(), (bufferLength > length) ? length : bufferLength);
				newBuffer = transfer->buffer;
			}

			libusb_fill_bulk_transfer(transfer, devHandle, endpoint, newBuffer, length, &this->transferCallback, transfer->user_data, timeout);
		}
		return 0;
	}

	/*
		fillBulkStreamTransfer(devHandle, endpoint, streamID, buffer, length, callback_fn, timeout)
	*/
	int Transfer::fillBulkStreamTransfer(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		DeviceHandle * iDeviceHandle = OBJECT_IFACE(DeviceHandle);
		libusb_device_handle * devHandle = iDeviceHandle->get(1);
		if (devHandle && stack->is<LUA_TNUMBER>(2) && stack->is<LUA_TNUMBER>(3) && stack->is<LUA_TFUNCTION>(6)){
			unsigned int timeout = 0;
			unsigned char * newBuffer = nullptr;
			int length = 0;
			char endpoint = stack->to<int>(2);
			uint32_t streamID = static_cast<uint32_t>(stack->to<LUA_NUMBER>(3));

			setTransferCallback(state, transfer, 6);
			if (stack->is<LUA_TNUMBER>(5)){
				length = stack->to<int>(5);
			}

			if (stack->is<LUA_TNUMBER>(7)){
				timeout = stack->to<int>(7);
			}

			if (stack->is<LUA_TSTRING>(4)){
				std::string buffer = stack->toLString(4);
				size_t bufferLength = buffer.length();
				size_t bufferSizeToCopy = bufferLength;
				if (length == 0){
					length = bufferLength;
				}
				reallocBuffer(state, transfer, length);
				memcpy(transfer->buffer, buffer.c_str(), (bufferLength > length) ? length : bufferLength);
				newBuffer = transfer->buffer;
			}

			libusb_fill_bulk_stream_transfer(transfer, devHandle, endpoint, streamID, newBuffer, length, &this->transferCallback, transfer->user_data, timeout);
		}
		return 0;
	}

	/*
		fillInterruptTransfer(devHandle, endpoint, buffer, length, callback_fn, timeout)
	*/
	int Transfer::fillInterruptTransfer(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		DeviceHandle * iDeviceHandle = OBJECT_IFACE(DeviceHandle);
		libusb_device_handle * devHandle = iDeviceHandle->get(1);
		if (devHandle && stack->is<LUA_TNUMBER>(2) && stack->is<LUA_TFUNCTION>(5)){
			unsigned int timeout = 0;
			unsigned char * newBuffer = nullptr;
			int length = 0;
			char endpoint = stack->to<int>(2);

			setTransferCallback(state, transfer, 5);
			if (stack->is<LUA_TNUMBER>(4)){
				length = stack->to<int>(4);
			}

			if (stack->is<LUA_TNUMBER>(6)){
				timeout = stack->to<int>(6);
			}

			if (stack->is<LUA_TSTRING>(3)){
				std::string buffer = stack->toLString(3);
				size_t bufferLength = buffer.length();
				size_t bufferSizeToCopy = bufferLength;
				if (length == 0){
					length = bufferLength;
				}
				reallocBuffer(state, transfer, length);
				memcpy(transfer->buffer, buffer.c_str(), (bufferLength > length) ? length : bufferLength);
				newBuffer = transfer->buffer;
			}

			libusb_fill_interrupt_transfer(transfer, devHandle, endpoint, newBuffer, length, &this->transferCallback, transfer->user_data, timeout);
		}
		return 0;
	}
	
	/*
		fillISOTransfer(devHandle, endpoint, buffer, length, numISOPackets, callback_fn, timeout)
	*/
	int Transfer::fillISOTransfer(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		DeviceHandle * iDeviceHandle = OBJECT_IFACE(DeviceHandle);
		libusb_device_handle * devHandle = iDeviceHandle->get(1);
		if (devHandle && stack->is<LUA_TNUMBER>(2) && stack->is<LUA_TNUMBER>(5) && stack->is<LUA_TFUNCTION>(6)){
			unsigned int timeout = 0;
			unsigned char * newBuffer = nullptr;
			int length = 0;
			char endpoint = stack->to<int>(2);
			int numISOPackets = stack->to<int>(5);

			setTransferCallback(state, transfer, 6);
			if (stack->is<LUA_TNUMBER>(4)){
				length = stack->to<int>(4);
			}

			if (stack->is<LUA_TNUMBER>(7)){
				timeout = stack->to<int>(7);
			}

			if (stack->is<LUA_TSTRING>(3)){
				std::string buffer = stack->toLString(3);
				size_t bufferLength = buffer.length();
				size_t bufferSizeToCopy = bufferLength;
				if (length == 0){
					length = bufferLength;
				}
				reallocBuffer(state, transfer, length);
				memcpy(transfer->buffer, buffer.c_str(), (bufferLength > length) ? length : bufferLength);
				newBuffer = transfer->buffer;
			}

			libusb_fill_iso_transfer(transfer, devHandle, endpoint, newBuffer, length, numISOPackets, &this->transferCallback, transfer->user_data, timeout);
		}
		return 0;
	}

	void Transfer::transferCallback(libusb_transfer *transfer){
		TransferData * transferData = static_cast<TransferData*>(transfer->user_data);
		if (transferData){
			State * state = transferData->state;
			Stack * stack = state->stack;
			stack->regValue(transferData->fnRef);
			if (stack->is<LUA_TFUNCTION>(-1)){
				Transfer * iTransfer = state->getInterface<Transfer>("luausb_Transfer");
				iTransfer->push(transfer);
				stack->call(1, 0);
			}
		}
	}

	int Transfer::getControlTransferData(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		stack->pushLString(reinterpret_cast<char*>(libusb_control_transfer_get_data(transfer)), transfer->actual_length);
		return 1;
	}
	int Transfer::setControlTransferData(State & state, libusb_transfer * transfer){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1)){
			const std::string data = stack->toLString(1);
			int newLength = data.length();
			if ((newLength + LIBUSB_CONTROL_SETUP_SIZE) != transfer->length){
				reallocBuffer(state, transfer, newLength + LIBUSB_CONTROL_SETUP_SIZE, true);
			}
			memcpy(transfer->buffer + LIBUSB_CONTROL_SETUP_SIZE, data.c_str(), newLength);
		}
		return 0;
	}

	void initTransfer(State * state, Module & module){
		INIT_OBJECT(Transfer);
	}
};
