#include "objects/Context.hpp"
#include "objects/Device.hpp"
#include "objects/DeviceHandle.hpp"

namespace luausb {
	libusb_context * Context::constructor(State & state, bool & managed){
		libusb_context * _context = nullptr;
		libusb_init(&_context);
		return _context;
	}

	void Context::destructor(State & state, libusb_context * context){
		libusb_exit(context);
	}

	int Context::getDeviceList(State & state, libusb_context * context){
		Stack * stack = state.stack;
		Device * iDevice = OBJECT_IFACE(Device);

		libusb_device ** devices = nullptr;

		size_t count = libusb_get_device_list(context, &devices);
		
		stack->newTable();

		size_t i = 0;
		libusb_device * device = devices[i];

		while ((device = devices[i++]) != nullptr){
			stack->push<int>(i);
			iDevice->push(device, true);
			stack->setTable();
		}

		libusb_free_device_list(devices, 0);
		return 1;
	}

	int Context::setDebug(State & state, libusb_context * context){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			libusb_set_debug(context, stack->to<int>(1));
		}
		return 0;
	}

	int Context::open(State & state, libusb_context * context){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TNUMBER>(2)){
			libusb_device_handle * handle = libusb_open_device_with_vid_pid(context, stack->to<int>(1), stack->to<int>(2));
			if (handle){
				DeviceHandle * iDevHandle = OBJECT_IFACE(DeviceHandle);
				iDevHandle->push(handle, true);
				return 1;
			}
			else{
				stack->push<bool>(false);
				return 1;
			}
		}
		return 0;
	}

	void initContext(State * state, Module & module){
		INIT_OBJECT(Context);
	}
};
