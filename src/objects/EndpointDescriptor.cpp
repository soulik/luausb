#include "objects/EndpointDescriptor.hpp"
#include "objects/Context.hpp"
#include "objects/SSEndpointCompanionDescriptor.hpp"

namespace luausb {
	libusb_endpoint_descriptor * EndpointDescriptor::constructor(State & state, bool & managed){
		return nullptr;
	}

	void EndpointDescriptor::destructor(State & state, libusb_endpoint_descriptor * object){
		delete object;
	}

	int EndpointDescriptor::getLength(State & state, libusb_endpoint_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bLength);
		return 1;
	}
	int EndpointDescriptor::getDescriptorType(State & state, libusb_endpoint_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bDescriptorType);
		return 1;
	}
	int EndpointDescriptor::getEndpointAddress(State & state, libusb_endpoint_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bEndpointAddress);
		return 1;
	}
	int EndpointDescriptor::getAttributes(State & state, libusb_endpoint_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bmAttributes);
		return 1;
	}
	int EndpointDescriptor::getMaxPacketSize(State & state, libusb_endpoint_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->wMaxPacketSize);
		return 1;
	}
	int EndpointDescriptor::getInterval(State & state, libusb_endpoint_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bInterval);
		return 1;
	}
	int EndpointDescriptor::getRefresh(State & state, libusb_endpoint_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bRefresh);
		return 1;
	}
	int EndpointDescriptor::getSynchAddress(State & state, libusb_endpoint_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bSynchAddress);
		return 1;
	}
	int EndpointDescriptor::getExtra(State & state, libusb_endpoint_descriptor * descriptor){
		Stack * stack = state.stack;
		size_t length = descriptor->bLength - 3;
		const std::string data = std::string(reinterpret_cast<const char*>(descriptor->extra), descriptor->extra_length);
		stack->pushLString(data, length);
		return 1;
	}

	int EndpointDescriptor::getSSCompanionDescriptor(State & state, libusb_endpoint_descriptor * descriptor){
		Stack * stack = state.stack;
		Context * iContext = OBJECT_IFACE(Context);
		Context_wrapper * wrapper = iContext->get(1);
		libusb_context * context = wrapper->context;
		libusb_ss_endpoint_companion_descriptor * descriptor2 = nullptr;
		SSEndpointCompanionDescriptor * iDesc = OBJECT_IFACE(SSEndpointCompanionDescriptor);

		int result = 0;
		if ((result = libusb_get_ss_endpoint_companion_descriptor(context, descriptor, &descriptor2)) == LIBUSB_SUCCESS){
			iDesc->push(descriptor2, true);
			return 1;
		}
		else {
			stack->push<bool>(false);
			stack->push<int>(result);
			return 2;
		}
	}

	void initEndpointDescriptor(State * state, Module & module){
		INIT_OBJECT(EndpointDescriptor);
	}
};
