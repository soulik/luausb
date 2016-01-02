#include "objects/InterfaceDescriptor.hpp"
#include "objects/EndpointDescriptor.hpp"

namespace luausb {
	libusb_interface_descriptor * InterfaceDescriptor::constructor(State & state, bool & managed){
		return nullptr;
	}

	void InterfaceDescriptor::destructor(State & state, libusb_interface_descriptor * object){
		delete object;
	}

	int InterfaceDescriptor::getLength(State & state, libusb_interface_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bLength);
		return 1;
	}
	int InterfaceDescriptor::getDescriptorType(State & state, libusb_interface_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bDescriptorType);
		return 1;
	}
	int InterfaceDescriptor::getInterfaceNumber(State & state, libusb_interface_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bInterfaceNumber);
		return 1;
	}
	int InterfaceDescriptor::getAlternateSetting(State & state, libusb_interface_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bInterfaceNumber);
		return 1;
	}
	int InterfaceDescriptor::getNumEndpoint(State & state, libusb_interface_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bInterfaceNumber);
		return 1;
	}
	int InterfaceDescriptor::getInterfaceClass(State & state, libusb_interface_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bInterfaceNumber);
		return 1;
	}
	int InterfaceDescriptor::getInterfaceSubClass(State & state, libusb_interface_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bInterfaceNumber);
		return 1;
	}
	int InterfaceDescriptor::getInterfaceProtocol(State & state, libusb_interface_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bInterfaceNumber);
		return 1;
	}
	int InterfaceDescriptor::getInterface(State & state, libusb_interface_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bInterfaceNumber);
		return 1;
	}
	int InterfaceDescriptor::getEndpoints(State & state, libusb_interface_descriptor * descriptor){
		Stack * stack = state.stack;
		if (descriptor->endpoint){
			EndpointDescriptor * iEndpointDesc = OBJECT_IFACE(EndpointDescriptor);
			stack->setTable();
			for (size_t i = 0; i < descriptor->bNumEndpoints; i++){
				stack->push<int>(i+1);
				iEndpointDesc->push(const_cast<libusb_endpoint_descriptor *>(&descriptor->endpoint[i]));
				stack->setTable();
			}
		}
		else{
			stack->pushNil();
		}
		return 1;
	}
	int InterfaceDescriptor::getExtra(State & state, libusb_interface_descriptor * descriptor){
		Stack * stack = state.stack;
		size_t length = descriptor->bLength - 3;
		const std::string data = std::string(reinterpret_cast<const char*>(descriptor->extra), descriptor->extra_length);
		stack->pushLString(data, length);
		return 1;
	}

	void initInterfaceDescriptor(State * state, Module & module){
		INIT_OBJECT(InterfaceDescriptor);
	}
};
