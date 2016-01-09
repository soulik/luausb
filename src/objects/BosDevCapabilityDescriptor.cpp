#include "objects/BosDevCapabilityDescriptor.hpp"
#include "objects/Context.hpp"
#include "objects/USB20ExtensionDescriptor.hpp"
#include "objects/SSUSBDeviceCapabilityDescriptor.hpp"
#include "objects/ContainerIDDescriptor.hpp"

namespace luausb {
	libusb_bos_dev_capability_descriptor * BosDevCapabilityDescriptor::constructor(State & state, bool & managed){
		return nullptr;
	}

	void BosDevCapabilityDescriptor::destructor(State & state, libusb_bos_dev_capability_descriptor * descriptor){
		delete descriptor;
	}

	int BosDevCapabilityDescriptor::getLength(State & state, libusb_bos_dev_capability_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bLength);
		return 1;
	}

	int BosDevCapabilityDescriptor::getDescriptorType(State & state, libusb_bos_dev_capability_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bDescriptorType);
		return 1;
	}

	int BosDevCapabilityDescriptor::getDevCapabilityType(State & state, libusb_bos_dev_capability_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bDevCapabilityType);
		return 1;
	}

	int BosDevCapabilityDescriptor::getCapabilityData(State & state, libusb_bos_dev_capability_descriptor * descriptor){
		Stack * stack = state.stack;
		size_t length = descriptor->bLength - 3;
		const std::string data = std::string(reinterpret_cast<char*>(descriptor->dev_capability_data), length);
		stack->pushLString(data, length);
		return 1;
	}

	int BosDevCapabilityDescriptor::getUSB2ExtensionDescriptor(State & state, libusb_bos_dev_capability_descriptor * descriptor){
		Stack * stack = state.stack;
		Context * iContext = OBJECT_IFACE(Context);
		libusb_context * context = iContext->get(1);
		libusb_usb_2_0_extension_descriptor * descriptor2 = nullptr;
		USB20ExtensionDescriptor * iDesc = OBJECT_IFACE(USB20ExtensionDescriptor);
		int result = 0;
		if ((result = libusb_get_usb_2_0_extension_descriptor(context, descriptor, &descriptor2)) == LIBUSB_SUCCESS){
			iDesc->push(descriptor2, true);
			return 1;
		} else{
			stack->push<bool>(false);
			stack->push<int>(result);
			return 2;
		}
		
	}

	int BosDevCapabilityDescriptor::getSSUSBDeviceCapabilityDescriptor(State & state, libusb_bos_dev_capability_descriptor * descriptor){
		Stack * stack = state.stack;
		Context * iContext = OBJECT_IFACE(Context);
		libusb_context * context = iContext->get(1);
		libusb_ss_usb_device_capability_descriptor * descriptor2 = nullptr;
		SSUSBDeviceCapabilityDescriptor * iDesc = OBJECT_IFACE(SSUSBDeviceCapabilityDescriptor);
		int result = 0;
		if ((result = libusb_get_ss_usb_device_capability_descriptor(context, descriptor, &descriptor2)) == LIBUSB_SUCCESS){
			iDesc->push(descriptor2, true);
			return 1;
		} else {
			stack->push<bool>(false);
			stack->push<int>(result);
			return 2;
		}
	}

	int BosDevCapabilityDescriptor::getContainerIDDescriptor(State & state, libusb_bos_dev_capability_descriptor * descriptor){
		Stack * stack = state.stack;
		Context * iContext = OBJECT_IFACE(Context);
		libusb_context * context = iContext->get(1);
		libusb_container_id_descriptor * descriptor2 = nullptr;
		ContainerIDDescriptor * iDesc = OBJECT_IFACE(ContainerIDDescriptor);
		int result = 0;
		if ((result = libusb_get_container_id_descriptor(context, descriptor, &descriptor2)) == LIBUSB_SUCCESS){
			iDesc->push(descriptor2, true);
			return 1;
		}
		else {
			stack->push<bool>(false);
			stack->push<int>(result);
			return 2;
		}
	}

	void initBosDevCapabilityDescriptor(State * state, Module & module){
		INIT_OBJECT(BosDevCapabilityDescriptor);
	}
};
