#include "objects/BosDescriptor.hpp"
#include "objects/BosDevCapabilityDescriptor.hpp"

namespace luausb {
	libusb_bos_descriptor * BosDescriptor::constructor(State & state, bool & managed){
		return nullptr;
	}

	void BosDescriptor::destructor(State & state, libusb_bos_descriptor * descriptor){
		libusb_free_bos_descriptor(descriptor);
	}

	int BosDescriptor::getLength(State & state, libusb_bos_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bLength);
		return 1;
	}

	int BosDescriptor::getDescriptorType(State & state, libusb_bos_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bDescriptorType);
		return 1;
	}

	int BosDescriptor::getTotalLength(State & state, libusb_bos_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->wTotalLength);
		return 1;
	}

	int BosDescriptor::getNumDeviceCaps(State & state, libusb_bos_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bNumDeviceCaps);
		return 1;
	}

	int BosDescriptor::getDeviceCapabilities(State & state, libusb_bos_descriptor * descriptor){
		Stack * stack = state.stack;
		BosDevCapabilityDescriptor * iBOSDevCapDesc = OBJECT_IFACE(BosDevCapabilityDescriptor);

		stack->newTable();
		for (size_t i = 0; i < descriptor->bNumDeviceCaps; i++){
			libusb_bos_dev_capability_descriptor * capDesc = descriptor->dev_capability[i];
			stack->push<int>(i+1);
			iBOSDevCapDesc->push(capDesc, true);
			stack->setTable();
		}
		return 1;
	}

	void initBosDescriptor(State * state, Module & module){
		INIT_OBJECT(BosDescriptor);
	}
};
