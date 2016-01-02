#include "objects/SSEndpointCompanionDescriptor.hpp"

namespace luausb {
	libusb_ss_endpoint_companion_descriptor * SSEndpointCompanionDescriptor::constructor(State & state, bool & managed){
		return nullptr;
	}

	void SSEndpointCompanionDescriptor::destructor(State & state, libusb_ss_endpoint_companion_descriptor * descriptor){
		libusb_free_ss_endpoint_companion_descriptor(descriptor);
	}

	int SSEndpointCompanionDescriptor::getLength(State & state, libusb_ss_endpoint_companion_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bLength);
		return 1;
	}
	int SSEndpointCompanionDescriptor::getDescriptorType(State & state, libusb_ss_endpoint_companion_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bDescriptorType);
		return 1;
	}
	int SSEndpointCompanionDescriptor::getMaxBurst(State & state, libusb_ss_endpoint_companion_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bMaxBurst);
		return 1;
	}
	int SSEndpointCompanionDescriptor::getAttributes(State & state, libusb_ss_endpoint_companion_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bmAttributes);
		return 1;
	}
	int SSEndpointCompanionDescriptor::getBytesPerInterval(State & state, libusb_ss_endpoint_companion_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->wBytesPerInterval);
		return 1;
	}

	void initSSEndpointCompanionDescriptor(State * state, Module & module){
		INIT_OBJECT(SSEndpointCompanionDescriptor);
	}
};
