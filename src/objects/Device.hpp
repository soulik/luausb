#ifndef LUA_USB_OBJECTS_DEVICE_H
#define LUA_USB_OBJECTS_DEVICE_H

#include "common.hpp"

namespace luausb {
	class Device : public Object<libusb_device> {
	public:
		explicit Device(State * state) : Object<libusb_device>(state){
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

		libusb_device * constructor(State & state, bool & managed);

		void destructor(State & state, libusb_device * object);

		int getActiveConfigDescriptor(State & state, libusb_device * object);
		int getConfigDescriptors(State & state, libusb_device * object);
		int getDescriptor(State & state, libusb_device * object);
		int getDeviceSpeed(State & state, libusb_device * object);
		int getBusNumber(State & state, libusb_device * object);
		int getPortNumber(State & state, libusb_device * object);
		int getDeviceAddress(State & state, libusb_device * object);
		int getParent(State & state, libusb_device * object);
		int getPortNumbers(State & state, libusb_device * object);

		int getConfigDescriptor(State & state, libusb_device * object);
		int getConfigDescriptorByValue(State & state, libusb_device * object);

		int getMaxPacketSize(State & state, libusb_device * object);
		int getMaxISOPacketSize(State & state, libusb_device * object);
		int openDevice(State & state, libusb_device * object);
	};
};

#endif	
