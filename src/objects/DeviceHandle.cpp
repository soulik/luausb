#include "objects/DeviceHandle.hpp"
#include "objects/Device.hpp"
#include "objects/BosDescriptor.hpp"

namespace luausb {
	DeviceHandle_wrapper * DeviceHandle::constructor(State & state, bool & managed){
		DeviceHandle_wrapper * wrapper = new DeviceHandle_wrapper;
		wrapper->managed = true;
		return wrapper;
	}

	void DeviceHandle::destructor(State & state, DeviceHandle_wrapper * wrapper){
		if (wrapper->managed){
			libusb_close(wrapper->handle);
		}
		delete wrapper;
	}

	int DeviceHandle::getDevice(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		Device * iDev = OBJECT_IFACE(Device);
		libusb_device * device = libusb_get_device(wrapper->handle);

		if (device){
			Device_wrapper * wrapper = new Device_wrapper;
			wrapper->device = device;
			wrapper->device = false;
			iDev->push(wrapper, true);
		}
		else{
			stack->pushNil();
		}
		return 1;
	}

	int DeviceHandle::getConfiguration(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		int config = 0;
		if (libusb_get_configuration(wrapper->handle, &config) == 0){
			stack->push<int>(config);
		}
		else{
			stack->pushNil();
		}
		return 1;
	}

	int DeviceHandle::setConfiguration(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			libusb_set_configuration(wrapper->handle, stack->to<int>(1));
		}
		return 0;
	}

	int DeviceHandle::getBOSDescriptor(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		BosDescriptor * iBOSDesc = OBJECT_IFACE(BosDescriptor);
		libusb_bos_descriptor * BOSDesc = nullptr;
		int result = 0;
		if ((result = libusb_get_bos_descriptor(wrapper->handle, &BOSDesc)) == LIBUSB_SUCCESS){
			iBOSDesc->push(BOSDesc, true);
			return 1;
		}
		else{
			stack->push<bool>(false);
			stack->push<int>(result);
			return 2;
		}
	}

	int DeviceHandle::claimInterface(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			int result = 0;
			if ((result = libusb_claim_interface(wrapper->handle, stack->to<int>(1))) == LIBUSB_SUCCESS){
				stack->push<bool>(true);
				return 1;
			}
			else{
				stack->push<bool>(false);
				stack->push<int>(result);
				return 2;
			}	
		}
		return 0;
	}

	int DeviceHandle::releaseInterface(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			int result = 0;
			if ((result = libusb_release_interface(wrapper->handle, stack->to<int>(1))) == LIBUSB_SUCCESS){
				stack->push<bool>(true);
				return 1;
			}
			else{
				stack->push<bool>(false);
				stack->push<int>(result);
				return 2;
			}

		}
		return 0;
	}

	int DeviceHandle::setInterfaceAltSetting(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TNUMBER>(2)){
			int result = 0;
			if ((result = libusb_set_interface_alt_setting(wrapper->handle, stack->to<int>(1), stack->to<int>(2))) == LIBUSB_SUCCESS){
				stack->push<bool>(true);
				return 1;
			}
			else{
				stack->push<bool>(false);
				stack->push<int>(result);
				return 2;
			}
		}
		return 0;
	}

	int DeviceHandle::clearHalt(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		int result = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			int result = 0;
			if ((result = libusb_clear_halt(wrapper->handle, stack->to<int>(1))) == LIBUSB_SUCCESS){
				stack->push<bool>(true);
				return 1;
			}
			else{
				stack->push<bool>(false);
				stack->push<int>(result);
				return 2;
			}
		}
		return 0;
	}

	int DeviceHandle::resetDevice(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		int result = 0;
		if ((result = libusb_reset_device(wrapper->handle)) == LIBUSB_SUCCESS){
			stack->push<bool>(true);
			return 1;
		}
		else{
			stack->push<bool>(false);
			stack->push<int>(result);
			return 2;
		}
	}

	int DeviceHandle::kernelDriverActive(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		int result = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			int result = 0;
			if ((result = libusb_kernel_driver_active(wrapper->handle, stack->to<int>(1))) == LIBUSB_SUCCESS){
				stack->push<bool>(true);
				return 1;
			}
			else{
				stack->push<bool>(false);
				stack->push<int>(result);
				return 2;
			}
		}
		return 0;
	}
	int DeviceHandle::detachKernelDriver(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		int result = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			int result = libusb_detach_kernel_driver(wrapper->handle, stack->to<int>(1));
			if ((result >= 0) && (result <= 1)){
				stack->push<bool>(result == 1);
				return 1;
			}
			else{
				stack->push<bool>(false);
				stack->push<int>(result);
				return 2;
			}
		}
		return 0;
	}
	int DeviceHandle::attachKernelDriver(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		int result = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			int result = 0;
			if ((result = libusb_attach_kernel_driver(wrapper->handle, stack->to<int>(1))) == LIBUSB_SUCCESS){
				stack->push<bool>(true);
				return 1;
			}
			else{
				stack->push<bool>(false);
				stack->push<int>(result);
				return 2;
			}
		}
		return 0;
	}
	int DeviceHandle::setAutoDetachKernelDriver(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		int result = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			libusb_set_auto_detach_kernel_driver(wrapper->handle, stack->to<int>(1));
		}
		return 0;
	}

	int DeviceHandle::getDescriptor(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TNUMBER>(2)){
			size_t length = 1024;
			if (stack->is<LUA_TNUMBER>(3)){
				length = stack->to<int>(3);
			}
			char * descriptor = new char[length];
			
			int result = libusb_get_descriptor(wrapper->handle, stack->to<int>(1), stack->to<int>(2), reinterpret_cast<unsigned char*>(descriptor), length);
			if (result >= 0){
				stack->pushLString(descriptor, result);
				delete[] descriptor;
				return 1;
			}
			else{
				delete[] descriptor;
				stack->push<bool>(false);
				stack->push<int>(result);
				return 2;
			}
		}
		return 0;
	}

	int DeviceHandle::getStringDescriptor(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TNUMBER>(2)){
			size_t length = 1024;
			if (stack->is<LUA_TNUMBER>(3)){
				length = stack->to<int>(3);
			}
			char * descriptor = new char[length];

			int result = libusb_get_string_descriptor(wrapper->handle, stack->to<int>(1), stack->to<int>(2), reinterpret_cast<unsigned char*>(descriptor), length);
			if (result >= 0){
				stack->pushLString(descriptor, result);
				delete[] descriptor;
				return 1;
			}
			else{
				delete[] descriptor;
				stack->push<bool>(false);
				stack->push<int>(result);
				return 2;
			}
		}
		return 0;
	}

	int DeviceHandle::getStringDescriptorASCII(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			size_t length = 1024;
			if (stack->is<LUA_TNUMBER>(2)){
				length = stack->to<int>(2);
			}
			char * descriptor = new char[length];

			int result = libusb_get_string_descriptor_ascii(wrapper->handle, stack->to<int>(1), reinterpret_cast<unsigned char*>(descriptor), length);
			if (result >= 0){
				stack->pushLString(descriptor, result);
				delete[] descriptor;
				return 1;
			}
			else{
				delete[] descriptor;
				stack->push<bool>(false);
				stack->push<int>(result);
				return 2;
			}
		}
		return 0;
	}

	int DeviceHandle::controlTransfer(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TNUMBER>(2) && stack->is<LUA_TNUMBER>(3) && stack->is<LUA_TNUMBER>(4) && stack->is<LUA_TSTRING>(5)){
			const std::string data = stack->toLString(5);
			unsigned int timeout = 0;
			if (stack->is<LUA_TNUMBER>(6)){
				timeout = stack->to<int>(6);
			}
			int result = libusb_control_transfer(wrapper->handle,
				stack->to<int>(1),
				stack->to<int>(2),
				stack->to<int>(3),
				stack->to<int>(4),
				reinterpret_cast<unsigned char *>(const_cast<char *>(data.c_str())),
				data.length(),
				timeout
				);
			if (result >= 0){
				stack->push<bool>(true);
				return 1;
			}
			else{
				stack->push<bool>(false);
				stack->push<int>(result);
				return 2;
			}
		}
		return 0;
	}
	int DeviceHandle::bulkTransfer(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TSTRING>(2)){
			const std::string data = stack->toLString(2);
			unsigned int timeout = 0;
			int transfered = 0;
			if (stack->is<LUA_TNUMBER>(3)){
				timeout = stack->to<int>(3);
			}
			int result = libusb_bulk_transfer(wrapper->handle,
				stack->to<int>(1),
				reinterpret_cast<unsigned char *>(const_cast<char *>(data.c_str())),
				data.length(),
				&transfered,
				timeout
				);
			if (result >= 0){
				stack->push<int>(transfered);
				return 1;
			}
			else{
				stack->push<bool>(false);
				stack->push<int>(result);
				return 2;
			}
		}
		return 0;
	}
	int DeviceHandle::interruptTransfer(State & state, DeviceHandle_wrapper * wrapper){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TSTRING>(2)){
			const std::string data = stack->toLString(2);
			unsigned int timeout = 0;
			int transfered = 0;
			if (stack->is<LUA_TNUMBER>(3)){
				timeout = stack->to<int>(3);
			}
			int result = libusb_interrupt_transfer(wrapper->handle,
				stack->to<int>(1),
				reinterpret_cast<unsigned char *>(const_cast<char *>(data.c_str())),
				data.length(),
				&transfered,
				timeout
				);
			if (result >= 0){
				stack->push<int>(transfered);
				return 1;
			}
			else{
				stack->push<bool>(false);
				stack->push<int>(result);
				return 2;
			}
		}
		return 0;
	}

	void initDeviceHandle(State * state, Module & module){
		INIT_OBJECT(DeviceHandle);
	}
};
