#include "objects/Context.hpp"
#include "objects/Device.hpp"

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

	void initContext(State * state, Module & module){
		INIT_OBJECT(Context);
	}
};
