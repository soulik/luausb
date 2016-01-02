local usb = require 'luausb'

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

local d = c.devices

for _, device in ipairs(d) do
	local configs = device.configDescriptors
	local descriptor = device.descriptor
	print(device.bus, device.port, device.address, device.speed, #configs, descriptor)
end