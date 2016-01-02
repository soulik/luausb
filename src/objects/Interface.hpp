#ifndef LUA_USB_OBJECTS_INTERFACE_H
#define LUA_USB_OBJECTS_INTERFACE_H

#include "common.hpp"

namespace luausb {
	class Interface : public Object<libusb_interface> {
	public:
		explicit Interface(State * state) : Object<libusb_interface>(state){
			LUTOK_PROPERTY("altSettings", &Interface::getAltSettings, &Interface::nullMethod);
			LUTOK_PROPERTY("numAltSettings", &Interface::getNumAltSettings, &Interface::nullMethod);
		}

		libusb_interface * constructor(State & state, bool & managed);

		void destructor(State & state, libusb_interface * object);
		
		int getAltSettings(State & state, libusb_interface * object);
		int getNumAltSettings(State & state, libusb_interface * object);
	};
};

#endif	
