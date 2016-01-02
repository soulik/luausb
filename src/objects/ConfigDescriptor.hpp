#ifndef LUA_USB_OBJECTS_CONFIGDESCRIPTOR_H
#define LUA_USB_OBJECTS_CONFIGDESCRIPTOR_H

#include "common.hpp"

namespace luausb {
	class ConfigDescriptor : public Object<libusb_config_descriptor> {
	public:
		explicit ConfigDescriptor(State * state) : Object<libusb_config_descriptor>(state){
			LUTOK_PROPERTY("length", &ConfigDescriptor::getLength, &ConfigDescriptor::nullMethod);
			LUTOK_PROPERTY("descriptorType", &ConfigDescriptor::getDescriptorType, &ConfigDescriptor::nullMethod);
			LUTOK_PROPERTY("totalLength", &ConfigDescriptor::getTotalLength, &ConfigDescriptor::nullMethod);
			LUTOK_PROPERTY("numInterfaces", &ConfigDescriptor::getNumInterfaces, &ConfigDescriptor::nullMethod);
			LUTOK_PROPERTY("configurationValue", &ConfigDescriptor::getConfigurationValue, &ConfigDescriptor::nullMethod);
			LUTOK_PROPERTY("configuration", &ConfigDescriptor::getConfiguration, &ConfigDescriptor::nullMethod);
			LUTOK_PROPERTY("attributes", &ConfigDescriptor::getAttributes, &ConfigDescriptor::nullMethod);
			LUTOK_PROPERTY("maxPower", &ConfigDescriptor::getMaxPower, &ConfigDescriptor::nullMethod);
			LUTOK_PROPERTY("interface", &ConfigDescriptor::getInterface, &ConfigDescriptor::nullMethod);
			LUTOK_PROPERTY("extra", &ConfigDescriptor::getExtra, &ConfigDescriptor::nullMethod);
		}

		libusb_config_descriptor * constructor(State & state, bool & managed);

		void destructor(State & state, libusb_config_descriptor * descriptor);

		int getLength(State & state, libusb_config_descriptor * descriptor);
		int getDescriptorType(State & state, libusb_config_descriptor * descriptor);
		int getTotalLength(State & state, libusb_config_descriptor * descriptor);
		int getNumInterfaces(State & state, libusb_config_descriptor * descriptor);
		int getConfigurationValue(State & state, libusb_config_descriptor * descriptor);
		int getConfiguration(State & state, libusb_config_descriptor * descriptor);
		int getAttributes(State & state, libusb_config_descriptor * descriptor);
		int getMaxPower(State & state, libusb_config_descriptor * descriptor);
		int getInterface(State & state, libusb_config_descriptor * descriptor);
		int getExtra(State & state, libusb_config_descriptor * descriptor);
	};
};

#endif	
