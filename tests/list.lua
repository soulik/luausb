local usb = require 'luausb'

local function USB_assert(...)
	local result = select(1, ...)
	local errn = select(2, ...)
	if type(errn)=='number' and errn ~= 0 and result == false then
		return usb.getErrorString(errn)
		--error(usb.getErrorString(errn))
	else
		return ...
	end
end

print("Supported locales: ", table.concat(usb.getSupportedLocales(), ','))

print("libusb version: ")
for k, v in pairs(usb.getVersion()) do
	print('', k, v)
end

print("libusb capabilities: ")
for k,v in pairs {
	[usb.CAP_HAS_CAPABILITY] = 'Capability',
	[usb.CAP_HAS_HOTPLUG] = 'Hotplug',
	[usb.CAP_HAS_HID_ACCESS] = 'HID Access',
	[usb.CAP_SUPPORTS_DETACH_KERNEL_DRIVER] = 'Detach Kernel Driver',
} do
	print('', v, usb.hasCapability(k))
end

print("libusb devices: ")
local c = usb.Context()
--c.debug = 4

local d = c.devices

for _, device in ipairs(d) do
	local configs = device.configDescriptors
	local descriptor = device.descriptor
	print(("Bus: %4d Port: %4d Address: %4d Class: %4d Sub-Class: %4d Vendor: %04X Product: %04X BCD: %04X"):format(
		device.bus, device.port, device.address, descriptor.deviceClass, descriptor.deviceSubClass, descriptor.IDVendor, descriptor.IDProduct, descriptor.BCDDevice
	))
	do
		local handle,errn = device.open()
		if handle then
			print(("Manufacturer: %q Product: %q S/N: %q"):format(
				USB_assert(handle.getStringDescriptorASCII(descriptor.manufacturer)),
				USB_assert(handle.getStringDescriptorASCII(descriptor.product)),
				USB_assert(handle.getStringDescriptorASCII(descriptor.serialNumber))
			))
		else
			print(usb.getErrorString(errn))
		end
	end
	--device.speed, #configs
end