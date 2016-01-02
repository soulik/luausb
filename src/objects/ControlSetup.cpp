#include "objects/ControlSetup.hpp"

namespace luausb {
	libusb_control_setup * ControlSetup::constructor(State & state, bool & managed){
		return nullptr;
	}

	void ControlSetup::destructor(State & state, libusb_control_setup * object){
		delete object;
	}

	int ControlSetup::getRequestType(State & state, libusb_control_setup * setup){
		Stack * stack = state.stack;
		stack->push<int>(setup->bmRequestType);
		return 1;
	}
	int ControlSetup::getRequest(State & state, libusb_control_setup * setup){
		Stack * stack = state.stack;
		stack->push<int>(setup->bRequest);
		return 1;
	}
	int ControlSetup::getValue(State & state, libusb_control_setup * setup){
		Stack * stack = state.stack;
		stack->push<int>(setup->wValue);
		return 1;
	}
	int ControlSetup::getIndex(State & state, libusb_control_setup * setup){
		Stack * stack = state.stack;
		stack->push<int>(setup->wIndex);
		return 1;
	}
	int ControlSetup::getLength(State & state, libusb_control_setup * setup){
		Stack * stack = state.stack;
		stack->push<int>(setup->wLength);
		return 1;
	}

	void initControlSetup(State * state, Module & module){
		INIT_OBJECT(ControlSetup);
	}
};
