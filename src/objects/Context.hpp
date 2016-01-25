#ifndef LUA_USB_OBJECTS_CONTEXT_H
#define LUA_USB_OBJECTS_CONTEXT_H

#include "common.hpp"

namespace luausb {
	struct Context_wrapper {
		libusb_context * context;
	};

	class Context : public Object<Context_wrapper> {
	public:
		explicit Context(State * state) : Object<Context_wrapper>(state){
			LUTOK_PROPERTY("devices", &Context::getDeviceList, &Context::nullMethod);
			LUTOK_PROPERTY("debug", &Context::nullMethod, &Context::setDebug);
			LUTOK_METHOD("open", &Context::open);

			LUTOK_METHOD("tryLockEvents", &Context::tryLockEvents);
			LUTOK_METHOD("lockEvents", &Context::lockEvents);
			LUTOK_METHOD("unlockEvents", &Context::unlockEvents);
			LUTOK_METHOD("lockEventWaiters", &Context::lockEventWaiters);
			LUTOK_METHOD("unlockEventWaiters", &Context::unlockEventWaiters);

			LUTOK_METHOD("handleEvents", &Context::handleEvents);
			LUTOK_METHOD("waitForEvent", &Context::waitForEvent);

			LUTOK_PROPERTY("eventHandlingOK", &Context::eventHandlingOK, &Context::nullMethod);
			LUTOK_PROPERTY("eventHandlerActive", &Context::eventHandlerActive, &Context::nullMethod);
		}

		Context_wrapper * constructor(State & state, bool & managed);

		void destructor(State & state, Context_wrapper * wrapper);

		int getDeviceList(State & state, Context_wrapper * wrapper);
		int setDebug(State & state, Context_wrapper * wrapper);

		int open(State & state, Context_wrapper * wrapper);

		int tryLockEvents(State & state, Context_wrapper * wrapper);
		int lockEvents(State & state, Context_wrapper * wrapper);
		int unlockEvents(State & state, Context_wrapper * wrapper);
		int lockEventWaiters(State & state, Context_wrapper * wrapper);
		int unlockEventWaiters(State & state, Context_wrapper * wrapper);
		int handleEvents(State & state, Context_wrapper * wrapper);
		int waitForEvent(State & state, Context_wrapper * wrapper);
		int eventHandlingOK(State & state, Context_wrapper * wrapper);
		int eventHandlerActive(State & state, Context_wrapper * wrapper);
	};
};

#endif	
