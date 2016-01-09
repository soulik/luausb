#ifndef LUA_USB_OBJECTS_CONTEXT_H
#define LUA_USB_OBJECTS_CONTEXT_H

#include "common.hpp"

namespace luausb {
	class Context : public Object<libusb_context> {
	public:
		explicit Context(State * state) : Object<libusb_context>(state){
			LUTOK_PROPERTY("devices", &Context::getDeviceList, &Context::nullMethod);
			LUTOK_PROPERTY("debug", &Context::nullMethod, &Context::setDebug);
			LUTOK_METHOD("open", &Context::open);
		}

		libusb_context * constructor(State & state, bool & managed);

		void destructor(State & state, libusb_context * context);

		int getDeviceList(State & state, libusb_context * context);
		int setDebug(State & state, libusb_context * context);

		int open(State & state, libusb_context * context);
	};
};

#endif	
