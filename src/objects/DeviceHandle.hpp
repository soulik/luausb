#ifndef LUA_USB_OBJECTS_DEVICEHANDLE_H
#define LUA_USB_OBJECTS_DEVICEHANDLE_H

#include "common.hpp"

namespace luausb {
	struct DeviceHandle_wrapper {
		DeviceHandle_wrapper(){
			handle = nullptr;
			managed = false;
		}
		libusb_device_handle * handle;
		bool managed;
	};

	class DeviceHandle : public Object<DeviceHandle_wrapper> {
	public:
		explicit DeviceHandle(State * state) : Object<DeviceHandle_wrapper>(state){
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

		DeviceHandle_wrapper * constructor(State & state, bool & managed);

		void destructor(State & state, DeviceHandle_wrapper * handle);

		int getDevice(State & state, DeviceHandle_wrapper * handle);
		int getConfiguration(State & state, DeviceHandle_wrapper * handle);
		int setConfiguration(State & state, DeviceHandle_wrapper * handle);
		int getBOSDescriptor(State & state, DeviceHandle_wrapper * handle);

		int getDescriptor(State & state, DeviceHandle_wrapper * handle);
		int getStringDescriptor(State & state, DeviceHandle_wrapper * handle);
		int getStringDescriptorASCII(State & state, DeviceHandle_wrapper * handle);

		int claimInterface(State & state, DeviceHandle_wrapper * handle);
		int releaseInterface(State & state, DeviceHandle_wrapper * handle);
		int setInterfaceAltSetting(State & state, DeviceHandle_wrapper * handle);
		int clearHalt(State & state, DeviceHandle_wrapper * handle);
		int resetDevice(State & state, DeviceHandle_wrapper * handle);

		int kernelDriverActive(State & state, DeviceHandle_wrapper * handle);
		int detachKernelDriver(State & state, DeviceHandle_wrapper * handle);
		int attachKernelDriver(State & state, DeviceHandle_wrapper * handle);
		int setAutoDetachKernelDriver(State & state, DeviceHandle_wrapper * handle);

		int controlTransfer(State & state, DeviceHandle_wrapper * handle);
		int bulkTransfer(State & state, DeviceHandle_wrapper * handle);
		int interruptTransfer(State & state, DeviceHandle_wrapper * handle);
	};
};

#endif	
