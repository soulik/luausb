#include "objects/Device.hpp"
#include "objects/ConfigDescriptor.hpp"
#include "objects/DeviceDescriptor.hpp"
#include "objects/DeviceHandle.hpp"

namespace luausb {
	Device_wrapper * Device::constructor(State & state, bool & managed){
		Device_wrapper * wrapper = new Device_wrapper;
		wrapper->managed = true;
		return wrapper;
	}

	void Device::destructor(State & state, Device_wrapper * wrapper){
		if (wrapper->managed){
			libusb_unref_device(wrapper->device);
		}
		delete wrapper;
	}

	int Device::getActiveConfigDescriptor(State & state, Device_wrapper * object){
		Stack * stack = state.stack;
		ConfigDescriptor * iConfDesc = OBJECT_IFACE(ConfigDescriptor);
		libusb_config_descriptor * config = nullptr;
		int result = 0;
		if ((result = libusb_get_active_config_descriptor(object->device, &config)) == LIBUSB_SUCCESS){
			iConfDesc->push(config, true);
			return 1;
		}
		else{
			stack->push<bool>(false);
			stack->push<bool>(result);
			return 2;
		}
	}

	int Device::getConfigDescriptors(State & state, Device_wrapper * object){
		Stack * stack = state.stack;
		ConfigDescriptor * iConfDesc = OBJECT_IFACE(ConfigDescriptor);

		libusb_device_descriptor descriptor;
		libusb_get_device_descriptor(object->device, &descriptor);
		
		stack->newTable();
		size_t li = 0;
		for (size_t i = 0; i < descriptor.bNumConfigurations; i++){
			libusb_config_descriptor * configDescriptor = nullptr;
			int errNum = libusb_get_config_descriptor(object->device, i, &configDescriptor);
			if (errNum == 0){
				stack->push<int>(++li);
				iConfDesc->push(configDescriptor, true);
				stack->setTable();
			}
		}
		
		return 1;
	}

	int Device::getDescriptor(State & state, Device_wrapper * object){
		Stack * stack = state.stack;
		DeviceDescriptor * iDevDesc = OBJECT_IFACE(DeviceDescriptor);
		libusb_device_descriptor * descriptor = new libusb_device_descriptor;
		int result = 0;
		if ((result = libusb_get_device_descriptor(object->device, descriptor)) == LIBUSB_SUCCESS){
			iDevDesc->push(descriptor, true);
			return 1;
		}
		else{
			stack->push<bool>(false);
			stack->push<bool>(result);
			return 2;
		}
	}

	int Device::getDeviceSpeed(State & state, Device_wrapper * object){
		Stack * stack = state.stack;
		stack->push<int>(libusb_get_device_speed(object->device));
		return 1;
	}

	int Device::getBusNumber(State & state, Device_wrapper * object){
		Stack * stack = state.stack;
		stack->push<int>(libusb_get_bus_number(object->device));
		return 1;
	}

	int Device::getPortNumber(State & state, Device_wrapper * object){
		Stack * stack = state.stack;
		stack->push<int>(libusb_get_port_number(object->device));
		return 1;
	}

	int Device::getDeviceAddress(State & state, Device_wrapper * object){
		Stack * stack = state.stack;
		stack->push<int>(libusb_get_device_address(object->device));
		return 1;
	}

	int Device::getParent(State & state, Device_wrapper * object){
		Stack * stack = state.stack;
		Device * iDev = OBJECT_IFACE(Device);

		libusb_device * parentDevice = libusb_get_parent(object->device);

		if (parentDevice){
			Device_wrapper * wrapper = new Device_wrapper;
			wrapper->device = parentDevice;
			wrapper->managed = false;
			iDev->push(wrapper, true);
		}else{
			stack->pushNil();
		}
		return 1;
	}

	int Device::getConfigDescriptor(State & state, Device_wrapper * object){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			ConfigDescriptor * iConfDesc = OBJECT_IFACE(ConfigDescriptor);
			libusb_config_descriptor * descriptor = nullptr;
			int result = 0;
			if ((result = libusb_get_config_descriptor(object->device, stack->to<int>(1), &descriptor)) == LIBUSB_SUCCESS){
				iConfDesc->push(descriptor, true);
				return 1;
			}
			else{
				stack->push<bool>(false);
				stack->push<bool>(result);
				return 2;
			}
		}
		return 0;
	}

	int Device::getConfigDescriptorByValue(State & state, Device_wrapper * object){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			ConfigDescriptor * iConfDesc = OBJECT_IFACE(ConfigDescriptor);
			libusb_config_descriptor * descriptor = nullptr;
			int result = 0;
			if ((result = libusb_get_config_descriptor_by_value(object->device, stack->to<int>(1), &descriptor)) == LIBUSB_SUCCESS){
				iConfDesc->push(descriptor, true);
				return 1;
			}
			else{
				stack->push<bool>(false);
				stack->push<bool>(result);
				return 2;
			}
		}
		return 0;
	}

	int Device::getPortNumbers(State & state, Device_wrapper * object){
		Stack * stack = state.stack;
		if (LIBUSB_API_VERSION >= 0x01000102){
			uint8_t ports[8];
			int count = libusb_get_port_numbers(object->device, ports, 8);
			if (count != LIBUSB_ERROR_OVERFLOW){
				stack->newTable();
				for (int i = 0; i < count; i++){
					stack->push<int>(i+1);
					stack->push<int>(ports[i]);
					stack->setTable();
				}
				return 1;
			}
			else{
				return 0;
			}
		}
		else{
			return 0;
		}
	}

	int Device::getMaxPacketSize(State & state, Device_wrapper * object){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			int result = libusb_get_max_packet_size(object->device, stack->to<int>(1));
			if ((result != LIBUSB_ERROR_NOT_FOUND) && (result != LIBUSB_ERROR_OTHER)){
				stack->push<int>(result);
				return 1;
			}
			else{
				stack->push<bool>(false);
				stack->push<bool>(result);
				return 2;
			}
		}
		return 0;
	}

	int Device::getMaxISOPacketSize(State & state, Device_wrapper * object){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			int result = libusb_get_max_iso_packet_size(object->device, stack->to<int>(1));
			if ((result != LIBUSB_ERROR_NOT_FOUND) && (result != LIBUSB_ERROR_OTHER)){
				stack->push<int>(result);
				return 1;
			}
			else{
				stack->push<bool>(false);
				stack->push<bool>(result);
				return 2;
			}	
		}
		return 0;
	}

	int Device::openDevice(State & state, Device_wrapper * object){
		Stack * stack = state.stack;
		libusb_device_handle * handle = nullptr;
		int result = 0;
		if ((result = libusb_open(object->device, &handle)) == LIBUSB_SUCCESS){
			DeviceHandle * iDevHandle = OBJECT_IFACE(DeviceHandle);
			DeviceHandle_wrapper * wrapper = new DeviceHandle_wrapper;
			wrapper->handle = handle;
			wrapper->managed = true;
			iDevHandle->push(wrapper, true);
			return 1;
		} else {
			stack->push<bool>(false);
			stack->push<int>(result);
			return 2;
		}
	}

	void initDevice(State * state, Module & module){
		INIT_OBJECT(Device);
	}
};
