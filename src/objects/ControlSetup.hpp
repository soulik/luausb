#ifndef LUA_USB_OBJECTS_CONTROLSETUP_H
#define LUA_USB_OBJECTS_CONTROLSETUP_H

#include "common.hpp"

namespace luausb {
	class ControlSetup : public Object<libusb_control_setup> {
	public:
		explicit ControlSetup(State * state) : Object<libusb_control_setup>(state){
			LUTOK_PROPERTY("requestType", &ControlSetup::getRequestType, &ControlSetup::nullMethod);
			LUTOK_PROPERTY("request", &ControlSetup::getRequest, &ControlSetup::nullMethod);
			LUTOK_PROPERTY("value", &ControlSetup::getValue, &ControlSetup::nullMethod);
			LUTOK_PROPERTY("index", &ControlSetup::getIndex, &ControlSetup::nullMethod);
			LUTOK_PROPERTY("length", &ControlSetup::getLength, &ControlSetup::nullMethod);
		}

		libusb_control_setup * constructor(State & state, bool & managed);

		void destructor(State & state, libusb_control_setup * setup);

		int getRequestType(State & state, libusb_control_setup * setup);
		int getRequest(State & state, libusb_control_setup * setup);
		int getValue(State & state, libusb_control_setup * setup);
		int getIndex(State & state, libusb_control_setup * setup);
		int getLength(State & state, libusb_control_setup * setup);
	};
};

#endif	
