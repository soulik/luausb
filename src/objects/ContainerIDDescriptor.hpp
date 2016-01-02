#ifndef LUA_USB_OBJECTS_CONTAINERIDDESCRIPTOR_H
#define LUA_USB_OBJECTS_CONTAINERIDDESCRIPTOR_H

#include "common.hpp"

namespace luausb {
	class ContainerIDDescriptor : public Object<libusb_container_id_descriptor> {
	public:
		explicit ContainerIDDescriptor(State * state) : Object<libusb_container_id_descriptor>(state){
			LUTOK_PROPERTY("length", &ContainerIDDescriptor::getLength, &ContainerIDDescriptor::nullMethod);
			LUTOK_PROPERTY("descriptorType", &ContainerIDDescriptor::getDescriptorType, &ContainerIDDescriptor::nullMethod);
			LUTOK_PROPERTY("capabilityType", &ContainerIDDescriptor::getDevCapabilityType, &ContainerIDDescriptor::nullMethod);
			LUTOK_PROPERTY("ID", &ContainerIDDescriptor::getContainerID, &ContainerIDDescriptor::nullMethod);

		}

		libusb_container_id_descriptor * constructor(State & state, bool & managed);

		void destructor(State & state, libusb_container_id_descriptor * descriptor);

		int getLength(State & state, libusb_container_id_descriptor * descriptor);
		int getDescriptorType(State & state, libusb_container_id_descriptor * descriptor);
		int getDevCapabilityType(State & state, libusb_container_id_descriptor * descriptor);
		int getContainerID(State & state, libusb_container_id_descriptor * descriptor);
	};
};

#endif	
