#include "objects/ContainerIDDescriptor.hpp"

namespace luausb {
	libusb_container_id_descriptor * ContainerIDDescriptor::constructor(State & state, bool & managed){
		return nullptr;
	}

	void ContainerIDDescriptor::destructor(State & state, libusb_container_id_descriptor * descriptor){
		libusb_free_container_id_descriptor(descriptor);
	}

	int ContainerIDDescriptor::getLength(State & state, libusb_container_id_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bLength);
		return 1;
	}

	int ContainerIDDescriptor::getDescriptorType(State & state, libusb_container_id_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bDescriptorType);
		return 1;
	}

	int ContainerIDDescriptor::getDevCapabilityType(State & state, libusb_container_id_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bDevCapabilityType);
		return 1;
	}

	int ContainerIDDescriptor::getContainerID(State & state, libusb_container_id_descriptor * descriptor){
		Stack * stack = state.stack;
		size_t length = 16;
		const std::string data = std::string(reinterpret_cast<char*>(descriptor->ContainerID), length);
		stack->pushLString(data, length);
		return 1;
	}

	void initContainerIDDescriptor(State * state, Module & module){
		INIT_OBJECT(ContainerIDDescriptor);
	}
};
