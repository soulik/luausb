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
		}

		Context_wrapper * constructor(State & state, bool & managed);

		void destructor(State & state, Context_wrapper * wrapper);

		int getDeviceList(State & state, Context_wrapper * wrapper);
		int setDebug(State & state, Context_wrapper * wrapper);

		int open(State & state, Context_wrapper * wrapper);
	};
};

#endif	
