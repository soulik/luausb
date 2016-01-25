local usb = require 'luausb'

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

		local function ControlTransfer(requestType, request, value, index, dataLength)
			assert(type(requestType)=='number' and type(request)=='number' and type(value)=='number' and type(index)=='number' and type(dataLength)=='number')
			local obj = {}

			local function complete_cb(transfer)
				if type(obj.complete)=='function' then
					obj.complete(transfer)
				end
			end

			local transfer_raw = usb.Transfer()
			obj.raw = transfer_raw

			local transferBuffer = transfer.fillControlSetup(requestType, request, value, index, dataLength)
			transfer_raw.fillControlTransfer(raw, transferBuffer, complete_cb)

			obj.send = function(data, timeout)
				transfer_raw.controlTransferData = data
				local r,m = transfer.submit()
				if not r then
					transfer_raw.cancel()
				end
				return c.handleEvents(timeout)
			end

			return obj
		end

		if raw then
			local dataTransfer = ControlTransfer(0x43, 0x01, 0x00, 0x00, 4)
			local resetTransfer = ControlTransfer(0x43, 0x02, 0x00, 0x00, 1)

			local obj = {
				raw = raw,
				send = function(data)
					if type(data) == 'table' then
						data = string.char(unpack(data))
					end
					return dataTransfer.send(data)
				end,
				reset = function()
					return resetTransfer.send(string.char(0x00))
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