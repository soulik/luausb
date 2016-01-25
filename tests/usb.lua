--[[
	easy luausb library wrapper
	Usage:

	local usb = require 'usb'

	local ctx = usb.new()

	-- connect to USB device VID: 0x1781, PID: 0x1111
	local device = assert(ctx.connect(0x1781, 0x1111))

	-- prepare async data transfer
	local dataTransfer = device.controlTransfer(0x43, 0x01, 0x00, 0x00, 4)

	-- send 4 bytes with control transfer
	dataTransfer.send {1, 255, 0, 0}

--]]
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

local function new()
	local obj = {}
	local c = usb.Context(); obj.context = c
	c.debug = 0

	local function connect(vid, pid)
		local raw,msg = USB_assert(c.open(vid, pid))

		local function controlTransfer(requestType, request, value, index, dataLength)
			assert(type(requestType)=='number' and type(request)=='number' and type(value)=='number' and type(index)=='number' and type(dataLength)=='number')
			local obj = {}

			local function complete_cb(transfer)
				if type(obj.complete)=='function' then
					obj.complete(transfer)
				end
			end

			local transfer = usb.Transfer()
			obj.raw = transfer

			local transferBuffer = transfer.fillControlSetup(requestType, request, value, index, dataLength)
			transfer.fillControlTransfer(raw, transferBuffer, complete_cb)

			obj.send = function(data, timeout)
				if type(data) == 'table' then
					data = string.char(unpack(data))
				end transfer
				.controlTransferData = data
				local r,m = transfer.submit()
				if not r then
					transfer.cancel()
				end
				return c.handleEvents(timeout)
			end

			return obj
		end

		if raw then
			local obj = {
				raw = raw,
				controlTransfer = controlTransfer,
				process = function()
					return c.handleEvents()
				end,
			}
			return obj
		else
			return false, "Can't open device"
		end
	end

	obj.connect = connect
	return obj
end

return {
	new = new,
}