#include "objects/DeviceDescriptor.hpp"

namespace luausb {
	libusb_device_descriptor * DeviceDescriptor::constructor(State & state, bool & managed){
		return nullptr;
	}

	void DeviceDescriptor::destructor(State & state, libusb_device_descriptor * descriptor){
		delete descriptor;
	}

	int DeviceDescriptor::getLength(State & state, libusb_device_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bLength);
		return 1;
	}
	int DeviceDescriptor::getDescriptorType(State & state, libusb_device_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bDescriptorType);
		return 1;
	}
	int DeviceDescriptor::getBCDUSB(State & state, libusb_device_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bcdUSB);
		return 1;
	}
	int DeviceDescriptor::getDeviceClass(State & state, libusb_device_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bDeviceClass);
		return 1;
	}
	int DeviceDescriptor::getDeviceSubClass(State & state, libusb_device_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bDeviceSubClass);
		return 1;
	}
	int DeviceDescriptor::getDeviceProtocol(State & state, libusb_device_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bDeviceProtocol);
		return 1;
	}
	int DeviceDescriptor::getMaxPacketSize0(State & state, libusb_device_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bMaxPacketSize0);
		return 1;
	}
	int DeviceDescriptor::getIDVendor(State & state, libusb_device_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->idVendor);
		return 1;
	}
	int DeviceDescriptor::getIDProduct(State & state, libusb_device_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->idProduct);
		return 1;
	}
	int DeviceDescriptor::getBCDDevice(State & state, libusb_device_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bcdDevice);
		return 1;
	}
	int DeviceDescriptor::getManufacturer(State & state, libusb_device_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->iManufacturer);
		return 1;
	}
	int DeviceDescriptor::getProduct(State & state, libusb_device_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->iProduct);
		return 1;
	}
	int DeviceDescriptor::getSerialNumber(State & state, libusb_device_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->iSerialNumber);
		return 1;
	}
	int DeviceDescriptor::getNumConfigurations(State & state, libusb_device_descriptor * descriptor){
		Stack * stack = state.stack;
		stack->push<int>(descriptor->bNumConfigurations);
		return 1;
	}

	void initDeviceDescriptor(State * state, Module & module){
		INIT_OBJECT(DeviceDescriptor);
	}
};
