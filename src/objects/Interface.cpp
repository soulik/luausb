#include "objects/Interface.hpp"
#include "objects/InterfaceDescriptor.hpp"

namespace luausb {
	libusb_interface * Interface::constructor(State & state, bool & managed){
		return nullptr;
	}

	void Interface::destructor(State & state, libusb_interface * object){
		delete object;
	}

	int Interface::getAltSettings(State & state, libusb_interface * object){
		Stack * stack = state.stack;
		InterfaceDescriptor * iInterfaceDesc = OBJECT_IFACE(InterfaceDescriptor);

		stack->newTable();
		for (size_t i = 0; i < object->num_altsetting; i++){
			stack->push<int>(i+1);
			iInterfaceDesc->push(const_cast<libusb_interface_descriptor *>(&(object->altsetting[i])));
			stack->setTable();
		}
		return 1;
	}

	int Interface::getNumAltSettings(State & state, libusb_interface * object){
		Stack * stack = state.stack;
		stack->push<int>(object->num_altsetting);
		return 1;
	}

	void initInterface(State * state, Module & module){
		INIT_OBJECT(Interface);
	}
};
