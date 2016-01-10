#ifndef LUA_USB_OBJECTS_DEVICE_H
#define LUA_USB_OBJECTS_DEVICE_H

#include "common.hpp"

namespace luausb {
	struct Device_wrapper {
		Device_wrapper(){
			device = nullptr;
			managed = false;
		}
		libusb_device * device;
		bool managed;
	};

	class Device : public Object<Device_wrapper> {
	public:
		explicit Device(State * state) : Object<Device_wrapper>(state){
			LUTOK_PROPERTY("activeConfigDescriptor", &Device::getActiveConfigDescriptor, &Device::nullMethod);
			LUTOK_PROPERTY("configDescriptors", &Device::getConfigDescriptors, &Device::nullMethod);
			LUTOK_PROPERTY("descriptor", &Device::getDescriptor, &Device::nullMethod);

			LUTOK_PROPERTY("speed", &Device::getDeviceSpeed, &Device::nullMethod);
			LUTOK_PROPERTY("bus", &Device::getBusNumber, &Device::nullMethod);
			LUTOK_PROPERTY("port", &Device::getPortNumber, &Device::nullMethod);
			LUTOK_PROPERTY("ports", &Device::getPortNumbers, &Device::nullMethod);
			LUTOK_PROPERTY("address", &Device::getDeviceAddress, &Device::nullMethod);
			LUTOK_PROPERTY("parent", &Device::getParent, &Device::nullMethod);
			
			LUTOK_METHOD("getConfigDescriptor", &Device::getConfigDescriptor);
			LUTOK_METHOD("getConfigDescriptorByValue", &Device::getConfigDescriptorByValue);

			LUTOK_METHOD("getMaxPacketSize", &Device::getMaxPacketSize);
			LUTOK_METHOD("getMaxISOPacketSize", &Device::getMaxISOPacketSize);
			LUTOK_METHOD("open", &Device::openDevice);
		}

		Device_wrapper * constructor(State & state, bool & managed);

		void destructor(State & state, Device_wrapper * wrapper);

		int getActiveConfigDescriptor(State & state, Device_wrapper * object);
		int getConfigDescriptors(State & state, Device_wrapper * object);
		int getDescriptor(State & state, Device_wrapper * object);
		int getDeviceSpeed(State & state, Device_wrapper * object);
		int getBusNumber(State & state, Device_wrapper * object);
		int getPortNumber(State & state, Device_wrapper * object);
		int getDeviceAddress(State & state, Device_wrapper * object);
		int getParent(State & state, Device_wrapper * object);
		int getPortNumbers(State & state, Device_wrapper * object);

		int getConfigDescriptor(State & state, Device_wrapper * object);
		int getConfigDescriptorByValue(State & state, Device_wrapper * object);

		int getMaxPacketSize(State & state, Device_wrapper * object);
		int getMaxISOPacketSize(State & state, Device_wrapper * object);
		int openDevice(State & state, Device_wrapper * object);
	};
};

#endif	
