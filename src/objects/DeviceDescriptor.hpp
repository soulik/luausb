#ifndef LUA_USB_OBJECTS_DEVICEDESCRIPTOR_H
#define LUA_USB_OBJECTS_DEVICEDESCRIPTOR_H

#include "common.hpp"

namespace luausb {
	class DeviceDescriptor : public Object<libusb_device_descriptor> {
	public:
		explicit DeviceDescriptor(State * state) : Object<libusb_device_descriptor>(state){
			LUTOK_PROPERTY("length", &DeviceDescriptor::getLength, &DeviceDescriptor::nullMethod);
			LUTOK_PROPERTY("descriptorType", &DeviceDescriptor::getDescriptorType, &DeviceDescriptor::nullMethod);
			LUTOK_PROPERTY("BCDUSB", &DeviceDescriptor::getBCDUSB, &DeviceDescriptor::nullMethod);
			LUTOK_PROPERTY("deviceClass", &DeviceDescriptor::getDeviceClass, &DeviceDescriptor::nullMethod);
			LUTOK_PROPERTY("deviceSubClass", &DeviceDescriptor::getDeviceSubClass, &DeviceDescriptor::nullMethod);
			LUTOK_PROPERTY("deviceProtocol", &DeviceDescriptor::getDeviceProtocol, &DeviceDescriptor::nullMethod);
			LUTOK_PROPERTY("maxPacketSize0", &DeviceDescriptor::getMaxPacketSize0, &DeviceDescriptor::nullMethod);
			LUTOK_PROPERTY("IDVendor", &DeviceDescriptor::getIDVendor, &DeviceDescriptor::nullMethod);
			LUTOK_PROPERTY("IDProduct", &DeviceDescriptor::getIDProduct, &DeviceDescriptor::nullMethod);
			LUTOK_PROPERTY("BCDDevice", &DeviceDescriptor::getBCDDevice, &DeviceDescriptor::nullMethod);
			LUTOK_PROPERTY("manufacturer", &DeviceDescriptor::getManufacturer, &DeviceDescriptor::nullMethod);
			LUTOK_PROPERTY("serialNumber", &DeviceDescriptor::getSerialNumber, &DeviceDescriptor::nullMethod);
			LUTOK_PROPERTY("numConfigurations", &DeviceDescriptor::getNumConfigurations, &DeviceDescriptor::nullMethod);
		}

		libusb_device_descriptor * constructor(State & state, bool & managed);

		void destructor(State & state, libusb_device_descriptor * descriptor);

		int getLength(State & state, libusb_device_descriptor * descriptor);
		int getDescriptorType(State & state, libusb_device_descriptor * descriptor);
		int getBCDUSB(State & state, libusb_device_descriptor * descriptor);
		int getDeviceClass(State & state, libusb_device_descriptor * descriptor);
		int getDeviceSubClass(State & state, libusb_device_descriptor * descriptor);
		int getDeviceProtocol(State & state, libusb_device_descriptor * descriptor);
		int getMaxPacketSize0(State & state, libusb_device_descriptor * descriptor);
		int getIDVendor(State & state, libusb_device_descriptor * descriptor);
		int getIDProduct(State & state, libusb_device_descriptor * descriptor);
		int getBCDDevice(State & state, libusb_device_descriptor * descriptor);
		int getManufacturer(State & state, libusb_device_descriptor * descriptor);
		int getSerialNumber(State & state, libusb_device_descriptor * descriptor);
		int getNumConfigurations(State & state, libusb_device_descriptor * descriptor);
	};
};

#endif	
