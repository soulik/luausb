#include "objects/ConfigDescriptor.hpp"
#include "objects/Interface.hpp"

namespace luausb {
	libusb_config_descriptor * ConfigDescriptor::constructor(State & state, bool & managed){
		return nullptr;
	}

	void ConfigDescriptor::destructor(State & state, libusb_config_descriptor * descriptor){
		libusb_free_config_descriptor(descriptor);
	}


	int ConfigDescriptor::getLength(State & state, libusb_config_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bLength);
		return 1;
	}
	int ConfigDescriptor::getDescriptorType(State & state, libusb_config_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bDescriptorType);
		return 1;
	}

	int ConfigDescriptor::getTotalLength(State & state, libusb_config_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->wTotalLength);
		return 1;
	}
	int ConfigDescriptor::getNumInterfaces(State & state, libusb_config_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bNumInterfaces);
		return 1;
	}
	int ConfigDescriptor::getConfigurationValue(State & state, libusb_config_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bConfigurationValue);
		return 1;
	}
	int ConfigDescriptor::getConfiguration(State & state, libusb_config_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->iConfiguration);
		return 1;
	}
	int ConfigDescriptor::getAttributes(State & state, libusb_config_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bmAttributes);
		return 1;
	}
	int ConfigDescriptor::getMaxPower(State & state, libusb_config_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->MaxPower);
		return 1;
	}
	int ConfigDescriptor::getInterface(State & state, libusb_config_descriptor * descriptor){
		Stack * stack = state.stack;
		if (descriptor->interface){
			Interface * iInterface = OBJECT_IFACE(Interface);
			iInterface->push(const_cast<libusb_interface *>(descriptor->interface));
		}
		else{
			stack->pushNil();
		}
		return 1;
	}
	int ConfigDescriptor::getExtra(State & state, libusb_config_descriptor * descriptor){
		Stack * stack = state.stack;
		size_t length = descriptor->bLength - 3;
		const std::string data = std::string(reinterpret_cast<const char*>(descriptor->extra), descriptor->extra_length);
		stack->pushLString(std::string(data, length));
		return 1;
	}

	void initConfigDescriptor(State * state, Module & module){
		INIT_OBJECT(ConfigDescriptor);
	}
};
