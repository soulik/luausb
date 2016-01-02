#ifndef LUA_USB_OBJECTS_DEVICEHANDLE_H
#define LUA_USB_OBJECTS_DEVICEHANDLE_H

#include "common.hpp"

namespace luausb {
	class DeviceHandle : public Object<libusb_device_handle> {
	public:
		explicit DeviceHandle(State * state) : Object<libusb_device_handle>(state){
			LUTOK_PROPERTY("device", &DeviceHandle::getDevice, &DeviceHandle::nullMethod);
			LUTOK_PROPERTY("config", &DeviceHandle::getConfiguration, &DeviceHandle::setConfiguration);
			LUTOK_PROPERTY("BOSdescriptor", &DeviceHandle::getBOSDescriptor, &DeviceHandle::nullMethod);

			LUTOK_METHOD("getDescriptor", &DeviceHandle::getDescriptor);
			LUTOK_METHOD("getStringDescriptor", &DeviceHandle::getStringDescriptor);
			LUTOK_METHOD("getStringDescriptorASCII", &DeviceHandle::getStringDescriptorASCII);

			LUTOK_METHOD("claim", &DeviceHandle::claimInterface);
			LUTOK_METHOD("release", &DeviceHandle::releaseInterface);
			LUTOK_METHOD("setInterfaceAltSetting", &DeviceHandle::setInterfaceAltSetting);
			LUTOK_METHOD("clearHalt", &DeviceHandle::clearHalt);
			LUTOK_METHOD("reset", &DeviceHandle::resetDevice);

			LUTOK_PROPERTY("autoDetachKernelDriver", &DeviceHandle::nullMethod, &DeviceHandle::setAutoDetachKernelDriver);
			LUTOK_METHOD("kernelDriverActive", &DeviceHandle::kernelDriverActive);
			LUTOK_METHOD("detachKernelDriver", &DeviceHandle::detachKernelDriver);
			LUTOK_METHOD("attachKernelDriver", &DeviceHandle::attachKernelDriver);

			LUTOK_METHOD("controlTransfer", &DeviceHandle::controlTransfer);
			LUTOK_METHOD("bulkTransfer", &DeviceHandle::bulkTransfer);
			LUTOK_METHOD("interruptTransfer", &DeviceHandle::interruptTransfer);
		}

		libusb_device_handle * constructor(State & state, bool & managed);

		void destructor(State & state, libusb_device_handle * handle);

		int getDevice(State & state, libusb_device_handle * handle);
		int getConfiguration(State & state, libusb_device_handle * handle);
		int setConfiguration(State & state, libusb_device_handle * handle);
		int getBOSDescriptor(State & state, libusb_device_handle * handle);

		int getDescriptor(State & state, libusb_device_handle * handle);
		int getStringDescriptor(State & state, libusb_device_handle * handle);
		int getStringDescriptorASCII(State & state, libusb_device_handle * handle);

		int claimInterface(State & state, libusb_device_handle * handle);
		int releaseInterface(State & state, libusb_device_handle * handle);
		int setInterfaceAltSetting(State & state, libusb_device_handle * handle);
		int clearHalt(State & state, libusb_device_handle * handle);
		int resetDevice(State & state, libusb_device_handle * handle);

		int kernelDriverActive(State & state, libusb_device_handle * handle);
		int detachKernelDriver(State & state, libusb_device_handle * handle);
		int attachKernelDriver(State & state, libusb_device_handle * handle);
		int setAutoDetachKernelDriver(State & state, libusb_device_handle * handle);

		int controlTransfer(State & state, libusb_device_handle * handle);
		int bulkTransfer(State & state, libusb_device_handle * handle);
		int interruptTransfer(State & state, libusb_device_handle * handle);
	};
};

#endif	
