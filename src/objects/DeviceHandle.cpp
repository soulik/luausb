#include "objects/DeviceHandle.hpp"
#include "objects/Device.hpp"
#include "objects/BosDescriptor.hpp"

namespace luausb {
	libusb_device_handle * DeviceHandle::constructor(State & state, bool & managed){
		return nullptr;
	}

	void DeviceHandle::destructor(State & state, libusb_device_handle * handle){
		libusb_close(handle);
	}

	int DeviceHandle::getDevice(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		Device * iDev = OBJECT_IFACE(Device);
		libusb_device * device = libusb_get_device(handle);
		if (device){
			iDev->push(device);
			
		}
		else{
			stack->pushNil();
		}
		return 1;
	}

	int DeviceHandle::getConfiguration(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		int config = 0;
		if (libusb_get_configuration(handle, &config) == 0){
			stack->push<int>(config);
		}
		else{
			stack->pushNil();
		}
		return 1;
	}

	int DeviceHandle::setConfiguration(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			libusb_set_configuration(handle, stack->to<int>(1));
		}
		return 0;
	}

	int DeviceHandle::getBOSDescriptor(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		BosDescriptor * iBOSDesc = OBJECT_IFACE(BosDescriptor);
		libusb_bos_descriptor * BOSDesc = nullptr;
		if (libusb_get_bos_descriptor(handle, &BOSDesc) == 0){
			iBOSDesc->push(BOSDesc, true);
		}
		else{
			stack->push<bool>(false);
		}
		return 1;
	}

	int DeviceHandle::claimInterface(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			int result = 0;
			if ((result = libusb_claim_interface(handle, stack->to<int>(1))) == 0){
				stack->push<bool>(true);
			}
			else{
				stack->push<int>(result);
			}
			return 1;
		}
		return 0;
	}

	int DeviceHandle::releaseInterface(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			int result = 0;
			if ((result = libusb_release_interface(handle, stack->to<int>(1))) == 0){
				stack->push<bool>(true);
			}
			else{
				stack->push<int>(result);
			}
			return 1;
		}
		return 0;
	}

	int DeviceHandle::setInterfaceAltSetting(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TNUMBER>(2)){
			int result = 0;
			if ((result = libusb_set_interface_alt_setting(handle, stack->to<int>(1), stack->to<int>(2))) == 0){
				stack->push<bool>(true);
			}
			else{
				stack->push<int>(result);
			}
			return 1;
		}
		return 0;
	}

	int DeviceHandle::clearHalt(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		int result = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			int result = 0;
			if ((result = libusb_clear_halt(handle, stack->to<int>(1))) == 0){
				stack->push<bool>(true);
			}
			else{
				stack->push<int>(result);
			}
			return 1;
		}
		return 0;
	}

	int DeviceHandle::resetDevice(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		int result = 0;
		if ((result = libusb_reset_device(handle)) == 0){
			stack->push<bool>(true);
		}
		else{
			stack->push<int>(result);
		}
		return 1;
	}

	int DeviceHandle::kernelDriverActive(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		int result = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			int result = 0;
			if ((result = libusb_kernel_driver_active(handle, stack->to<int>(1))) == 0){
				stack->push<bool>(true);
			}
			else{
				stack->push<int>(result);
			}
			return 1;
		}
		return 0;
	}
	int DeviceHandle::detachKernelDriver(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		int result = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			int result = libusb_detach_kernel_driver(handle, stack->to<int>(1));
			if ((result >= 0) && (result <= 1)){
				stack->push<bool>(result == 1);
			}
			else{
				stack->push<int>(result);
			}
			return 1;
		}
		return 0;
	}
	int DeviceHandle::attachKernelDriver(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		int result = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			int result = 0;
			if ((result = libusb_attach_kernel_driver(handle, stack->to<int>(1))) == 0){
				stack->push<bool>(true);
			}
			else{
				stack->push<int>(result);
			}
			return 1;
		}
		return 0;
	}
	int DeviceHandle::setAutoDetachKernelDriver(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		int result = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			libusb_set_auto_detach_kernel_driver(handle, stack->to<int>(1));
		}
		return 0;
	}

	int DeviceHandle::getDescriptor(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TNUMBER>(2)){
			size_t length = 1024;
			if (stack->is<LUA_TNUMBER>(3)){
				length = stack->to<int>(3);
			}
			char * descriptor = new char[length];
			
			int result = libusb_get_descriptor(handle, stack->to<int>(1), stack->to<int>(2), reinterpret_cast<unsigned char*>(descriptor), length);
			if (result >= 0){
				stack->pushLString(descriptor, result);
			}
			else{
				stack->push<int>(result);
			}

			delete[] descriptor;
			return 1;
		}
		return 0;
	}

	int DeviceHandle::getStringDescriptor(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TNUMBER>(2)){
			size_t length = 1024;
			if (stack->is<LUA_TNUMBER>(3)){
				length = stack->to<int>(3);
			}
			char * descriptor = new char[length];

			int result = libusb_get_string_descriptor(handle, stack->to<int>(1), stack->to<int>(2), reinterpret_cast<unsigned char*>(descriptor), length);
			if (result >= 0){
				stack->pushLString(descriptor, result);
			}
			else{
				stack->push<int>(result);
			}

			delete[] descriptor;
			return 1;
		}
		return 0;
	}

	int DeviceHandle::getStringDescriptorASCII(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			size_t length = 1024;
			if (stack->is<LUA_TNUMBER>(2)){
				length = stack->to<int>(2);
			}
			char * descriptor = new char[length];

			int result = libusb_get_string_descriptor_ascii(handle, stack->to<int>(1), reinterpret_cast<unsigned char*>(descriptor), length);
			if (result >= 0){
				stack->pushLString(descriptor, result);
			}
			else{
				stack->push<int>(result);
			}

			delete[] descriptor;
			return 1;
		}
		return 0;
	}

	int DeviceHandle::controlTransfer(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TNUMBER>(2) && stack->is<LUA_TNUMBER>(3) && stack->is<LUA_TNUMBER>(4) && stack->is<LUA_TSTRING>(5)){
			const std::string data = stack->toLString(5);
			unsigned int timeout = 0;
			if (stack->is<LUA_TNUMBER>(6)){
				timeout = stack->to<int>(6);
			}
			int result = libusb_control_transfer(handle,
				stack->to<int>(1),
				stack->to<int>(2),
				stack->to<int>(3),
				stack->to<int>(4),
				reinterpret_cast<unsigned char *>(const_cast<char *>(data.c_str())),
				data.length(),
				timeout
				);
			if (result == 0){
				stack->push<bool>(true);
			}
			else{
				stack->push<int>(result);
			}
			return 1;
		}
		return 0;
	}
	int DeviceHandle::bulkTransfer(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TSTRING>(2)){
			const std::string data = stack->toLString(2);
			unsigned int timeout = 0;
			int transfered = 0;
			if (stack->is<LUA_TNUMBER>(3)){
				timeout = stack->to<int>(3);
			}
			int result = libusb_bulk_transfer(handle,
				stack->to<int>(1),
				reinterpret_cast<unsigned char *>(const_cast<char *>(data.c_str())),
				data.length(),
				&transfered,
				timeout
				);
			if (result == 0){
				stack->push<int>(transfered);
			}
			else{
				stack->push<int>(result);
			}
			return 1;
		}
		return 0;
	}
	int DeviceHandle::interruptTransfer(State & state, libusb_device_handle * handle){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TSTRING>(2)){
			const std::string data = stack->toLString(2);
			unsigned int timeout = 0;
			int transfered = 0;
			if (stack->is<LUA_TNUMBER>(3)){
				timeout = stack->to<int>(3);
			}
			int result = libusb_interrupt_transfer(handle,
				stack->to<int>(1),
				reinterpret_cast<unsigned char *>(const_cast<char *>(data.c_str())),
				data.length(),
				&transfered,
				timeout
				);
			if (result == 0){
				stack->push<int>(transfered);
			}
			else{
				stack->push<int>(result);
			}
			return 1;
		}
		return 0;
	}

	void initDeviceHandle(State * state, Module & module){
		INIT_OBJECT(DeviceHandle);
	}
};
