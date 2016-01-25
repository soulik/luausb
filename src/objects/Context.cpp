#include "objects/Context.hpp"
#include "objects/Device.hpp"
#include "objects/DeviceHandle.hpp"

namespace luausb {
	Context_wrapper * Context::constructor(State & state, bool & managed){
		Context_wrapper * wrapper = new Context_wrapper;
		libusb_init(&wrapper->context);
		return wrapper;
	}

	void Context::destructor(State & state, Context_wrapper * wrapper){
		libusb_exit(wrapper->context);
		delete wrapper;
	}

	int Context::getDeviceList(State & state, Context_wrapper * wrapper){
		Stack * stack = state.stack;
		Device * iDevice = OBJECT_IFACE(Device);

		libusb_device ** devices = nullptr;

		size_t count = libusb_get_device_list(wrapper->context, &devices);
		
		stack->newTable();

		size_t i = 0;
		libusb_device * device = devices[i];

		while ((device = devices[i++]) != nullptr){
			Device_wrapper * wrapper = new Device_wrapper;
			wrapper->device = device;
			wrapper->managed = true;
			stack->push<int>(i);
			iDevice->push(wrapper, true);
			stack->setTable();
		}

		libusb_free_device_list(devices, 0);
		return 1;
	}

	int Context::setDebug(State & state, Context_wrapper * wrapper){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			libusb_set_debug(wrapper->context, stack->to<int>(1));
		}
		return 0;
	}

	int Context::open(State & state, Context_wrapper * wrapper){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TNUMBER>(2)){
			libusb_device_handle * handle = libusb_open_device_with_vid_pid(wrapper->context, stack->to<int>(1), stack->to<int>(2));
			if (handle){
				DeviceHandle * iDevHandle = OBJECT_IFACE(DeviceHandle);
				DeviceHandle_wrapper * wrapper = new DeviceHandle_wrapper;
				wrapper->handle = handle;
				wrapper->managed = true;
				iDevHandle->push(wrapper, true);
				return 1;
			}
			else{
				stack->push<bool>(false);
				return 1;
			}
		}
		return 0;
	}

	bool fillTimeval(State & state, timeval & tv, int index){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(index)){
			tv.tv_sec = stack->to<int>(index);
			tv.tv_usec = 0;
			return true;
		}
		else if (stack->is<LUA_TTABLE>(index)){
			stack->getField("sec", index);
			if (stack->is<LUA_TNUMBER>(-1)){
				tv.tv_sec = stack->to<int>(-1);
			}
			else{
				tv.tv_sec = 0;
			}
			stack->pop(1);

			stack->getField("usec", index);
			if (stack->is<LUA_TNUMBER>(-1)){
				tv.tv_usec = stack->to<int>(-1);
			}
			else{
				tv.tv_usec = 0;
			}
			stack->pop(1);
			return true;
		}
		else{
			return false;
		}
	}

	int Context::handleEvents(State & state, Context_wrapper * wrapper){
		Stack * stack = state.stack;
		int result = 0;
		
		timeval tv;
		bool timeValSet = fillTimeval(state, tv, 1);
		int completed;
		if (stack->is<LUA_TBOOLEAN>(2)){
			completed = (stack->to<bool>(2)) ? 1 : 0;
		}
		else{
			completed = -1;
		}

		if (timeValSet){
			if (completed >= 0){
				result = libusb_handle_events_timeout_completed(wrapper->context, &tv, &completed);
			}
			else{
				result = libusb_handle_events_timeout(wrapper->context, &tv);
			}
		}
		else{
			if (completed >= 0){
				result = libusb_handle_events_completed(wrapper->context, &completed);
			}
			else{
				result = libusb_handle_events(wrapper->context);
			}
		}

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

	int Context::tryLockEvents(State & state, Context_wrapper * wrapper){
		Stack * stack = state.stack;
		int result = 0;
		result = libusb_try_lock_events(wrapper->context);
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
	int Context::lockEvents(State & state, Context_wrapper * wrapper){
		Stack * stack = state.stack;
		libusb_lock_events(wrapper->context);
		stack->push<bool>(true);
		return 1;
	}
	int Context::unlockEvents(State & state, Context_wrapper * wrapper){
		Stack * stack = state.stack;
		libusb_unlock_events(wrapper->context);
		stack->push<bool>(true);
		return 1;
	}
	int Context::lockEventWaiters(State & state, Context_wrapper * wrapper){
		Stack * stack = state.stack;
		libusb_lock_event_waiters(wrapper->context);
		stack->push<bool>(true);
		return 1;
	}
	int Context::unlockEventWaiters(State & state, Context_wrapper * wrapper){
		Stack * stack = state.stack;
		libusb_unlock_event_waiters(wrapper->context);
		stack->push<bool>(true);
		return 1;
	}
	int Context::waitForEvent(State & state, Context_wrapper * wrapper){
		Stack * stack = state.stack;
		int result = 0;
		timeval tv;
		if (fillTimeval(state, tv, 1)){
			result = libusb_wait_for_event(wrapper->context, &tv);
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
		else{
			return 0;
		}
	}
	int Context::eventHandlingOK(State & state, Context_wrapper * wrapper){
		Stack * stack = state.stack;
		int result = 0;
		result = libusb_event_handling_ok(wrapper->context);
		stack->push<bool>(result == 1);
		return 1;
	}
	int Context::eventHandlerActive(State & state, Context_wrapper * wrapper){
		Stack * stack = state.stack;
		int result = 0;
		result = libusb_event_handler_active(wrapper->context);
		stack->push<bool>(result == 1);
		return 1;
	}


	void initContext(State * state, Module & module){
		INIT_OBJECT(Context);
	}
};
