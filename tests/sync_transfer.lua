local utils = require 'utils/time'
require 'utils/hexdump'

local usb = require 'luausb'
local sleep = utils.sleep
local bit = require 'bit'

local function USB_assert(...)
	local result = select(1, ...)
	local errn = select(2, ...)
	if type(errn)=='number' and errn ~= 0 and result == false then
		--return usb.getErrorString(errn)
		error(usb.getErrorString(errn))
	else
		return ...
	end
end

do
	local c = usb.Context()
	c.debug = 0
	local function adafruit_trinket()
		local raw,msg = USB_assert(c.open(0x1781, 0x1111))

		if raw then
			local obj = {
				raw = raw,
				send = function(data)
					if type(data) == 'table' then
						data = string.char(unpack(data))
					end
					return USB_assert(raw.controlTransfer(0x43, 0x01, 0x00, 0x00, data))
				end,
				reset = function()
					return USB_assert(raw.controlTransfer(0x43, 0x02, 0x00, 0x00, string.char(0x00)))
				end,
				process = function()
					return c.handleEvents()
				end,
			}
			return obj
		else
			return false, "Can't open device"
		end
	end

	local a = assert(adafruit_trinket())
	a.reset()
	a.send {1,0,0,0}
end