#include "common.hpp"
#include "constants.hpp"

namespace luausb {
	void initConstants(State * state, Module & module) {
		Stack * stack = state->stack;

		stack->setField<int>("SUCCESS", LIBUSB_SUCCESS);
		stack->setField<int>("ERROR_IO", LIBUSB_ERROR_IO);
		stack->setField<int>("ERROR_INVALID_PARAM", LIBUSB_ERROR_INVALID_PARAM);
		stack->setField<int>("ERROR_ACCESS", LIBUSB_ERROR_ACCESS);
		stack->setField<int>("ERROR_NO_DEVICE", LIBUSB_ERROR_NO_DEVICE);
		stack->setField<int>("ERROR_NOT_FOUND", LIBUSB_ERROR_NOT_FOUND);
		stack->setField<int>("ERROR_BUSY", LIBUSB_ERROR_BUSY);
		stack->setField<int>("ERROR_TIMEOUT", LIBUSB_ERROR_TIMEOUT);
		stack->setField<int>("ERROR_OVERFLOW", LIBUSB_ERROR_OVERFLOW);
		stack->setField<int>("ERROR_PIPE", LIBUSB_ERROR_PIPE);
		stack->setField<int>("ERROR_INTERRUPTED", LIBUSB_ERROR_INTERRUPTED);
		stack->setField<int>("ERROR_NO_MEM", LIBUSB_ERROR_NO_MEM);
		stack->setField<int>("ERROR_NOT_SUPPORTED", LIBUSB_ERROR_NOT_SUPPORTED);
		stack->setField<int>("ERROR_OTHER", LIBUSB_ERROR_OTHER);

		stack->setField<int>("SPEED_UNKNOWN", LIBUSB_SPEED_UNKNOWN);
		stack->setField<int>("SPEED_LOW", LIBUSB_SPEED_LOW);
		stack->setField<int>("SPEED_FULL", LIBUSB_SPEED_FULL);
		stack->setField<int>("SPEED_HIGH", LIBUSB_SPEED_HIGH);
		stack->setField<int>("SPEED_SUPER", LIBUSB_SPEED_SUPER);

		stack->setField<int>("LOW_SPEED_OPERATION", LIBUSB_LOW_SPEED_OPERATION);
		stack->setField<int>("FULL_SPEED_OPERATION", LIBUSB_FULL_SPEED_OPERATION);
		stack->setField<int>("HIGH_SPEED_OPERATION", LIBUSB_HIGH_SPEED_OPERATION);
		stack->setField<int>("SUPER_SPEED_OPERATION", LIBUSB_SUPER_SPEED_OPERATION);

		stack->setField<int>("BM_LPM_SUPPORT", LIBUSB_BM_LPM_SUPPORT);
		stack->setField<int>("BM_LTM_SUPPORT", LIBUSB_BM_LTM_SUPPORT);

		stack->setField<int>("BT_WIRELESS_USB_DEVICE_CAPABILITY", LIBUSB_BT_WIRELESS_USB_DEVICE_CAPABILITY);
		stack->setField<int>("BT_USB_2_0_EXTENSION", LIBUSB_BT_USB_2_0_EXTENSION);
		stack->setField<int>("BT_SS_USB_DEVICE_CAPABILITY", LIBUSB_BT_SS_USB_DEVICE_CAPABILITY);
		stack->setField<int>("BT_CONTAINER_ID", LIBUSB_BT_CONTAINER_ID);

		stack->setField<int>("REQUEST_GET_STATUS", LIBUSB_REQUEST_GET_STATUS);
		stack->setField<int>("REQUEST_CLEAR_FEATURE", LIBUSB_REQUEST_CLEAR_FEATURE);
		stack->setField<int>("REQUEST_SET_FEATURE", LIBUSB_REQUEST_SET_FEATURE);
		stack->setField<int>("REQUEST_SET_ADDRESS", LIBUSB_REQUEST_SET_ADDRESS);
		stack->setField<int>("REQUEST_GET_DESCRIPTOR", LIBUSB_REQUEST_GET_DESCRIPTOR);
		stack->setField<int>("REQUEST_SET_DESCRIPTOR", LIBUSB_REQUEST_SET_DESCRIPTOR);
		stack->setField<int>("REQUEST_GET_CONFIGURATION", LIBUSB_REQUEST_GET_CONFIGURATION);
		stack->setField<int>("REQUEST_SET_CONFIGURATION", LIBUSB_REQUEST_SET_CONFIGURATION);
		stack->setField<int>("REQUEST_GET_INTERFACE", LIBUSB_REQUEST_GET_INTERFACE);
		stack->setField<int>("REQUEST_SET_INTERFACE", LIBUSB_REQUEST_SET_INTERFACE);
		stack->setField<int>("REQUEST_SYNCH_FRAME", LIBUSB_REQUEST_SYNCH_FRAME);
		stack->setField<int>("REQUEST_SET_SEL", LIBUSB_REQUEST_SET_SEL);
		stack->setField<int>("SET_ISOCH_DELAY", LIBUSB_SET_ISOCH_DELAY);

		stack->setField<int>("REQUEST_TYPE_STANDARD", LIBUSB_REQUEST_TYPE_STANDARD);
		stack->setField<int>("REQUEST_TYPE_CLASS", LIBUSB_REQUEST_TYPE_CLASS);
		stack->setField<int>("REQUEST_TYPE_VENDOR", LIBUSB_REQUEST_TYPE_VENDOR);
		stack->setField<int>("REQUEST_TYPE_RESERVED", LIBUSB_REQUEST_TYPE_RESERVED);

		stack->setField<int>("RECIPIENT_DEVICE", LIBUSB_RECIPIENT_DEVICE);
		stack->setField<int>("RECIPIENT_INTERFACE", LIBUSB_RECIPIENT_INTERFACE);
		stack->setField<int>("RECIPIENT_ENDPOINT", LIBUSB_RECIPIENT_ENDPOINT);
		stack->setField<int>("RECIPIENT_OTHER", LIBUSB_RECIPIENT_OTHER);

		stack->setField<int>("CAP_HAS_CAPABILITY", LIBUSB_CAP_HAS_CAPABILITY);
		stack->setField<int>("CAP_HAS_HOTPLUG", LIBUSB_CAP_HAS_HOTPLUG);
		stack->setField<int>("CAP_HAS_HID_ACCESS", LIBUSB_CAP_HAS_HID_ACCESS);
		stack->setField<int>("CAP_SUPPORTS_DETACH_KERNEL_DRIVER", LIBUSB_CAP_SUPPORTS_DETACH_KERNEL_DRIVER);

		stack->setField<int>("CLASS_PER_INTERFACE", LIBUSB_CLASS_PER_INTERFACE);
		stack->setField<int>("CLASS_AUDIO", LIBUSB_CLASS_AUDIO);
		stack->setField<int>("CLASS_COMM", LIBUSB_CLASS_COMM);
		stack->setField<int>("CLASS_HID", LIBUSB_CLASS_HID);
		stack->setField<int>("CLASS_PHYSICAL", LIBUSB_CLASS_PHYSICAL);
		stack->setField<int>("CLASS_PRINTER", LIBUSB_CLASS_PRINTER);
		stack->setField<int>("CLASS_PTP", LIBUSB_CLASS_PTP);
		stack->setField<int>("CLASS_IMAGE", LIBUSB_CLASS_IMAGE);
		stack->setField<int>("CLASS_MASS_STORAGE", LIBUSB_CLASS_MASS_STORAGE);
		stack->setField<int>("CLASS_HUB", LIBUSB_CLASS_HUB);
		stack->setField<int>("CLASS_DATA", LIBUSB_CLASS_DATA);
		stack->setField<int>("CLASS_SMART_CARD", LIBUSB_CLASS_SMART_CARD);
		stack->setField<int>("CLASS_CONTENT_SECURITY", LIBUSB_CLASS_CONTENT_SECURITY);
		stack->setField<int>("CLASS_VIDEO", LIBUSB_CLASS_VIDEO);
		stack->setField<int>("CLASS_PERSONAL_HEALTHCARE", LIBUSB_CLASS_PERSONAL_HEALTHCARE);
		stack->setField<int>("CLASS_DIAGNOSTIC_DEVICE", LIBUSB_CLASS_DIAGNOSTIC_DEVICE);
		stack->setField<int>("CLASS_WIRELESS", LIBUSB_CLASS_WIRELESS);
		stack->setField<int>("CLASS_APPLICATION", LIBUSB_CLASS_APPLICATION);
		stack->setField<int>("CLASS_VENDOR_SPEC", LIBUSB_CLASS_VENDOR_SPEC);

		stack->setField<int>("DT_DEVICE", LIBUSB_DT_DEVICE);
		stack->setField<int>("DT_CONFIG", LIBUSB_DT_CONFIG);
		stack->setField<int>("DT_STRING", LIBUSB_DT_STRING);
		stack->setField<int>("DT_INTERFACE", LIBUSB_DT_INTERFACE);
		stack->setField<int>("DT_ENDPOINT", LIBUSB_DT_ENDPOINT);
		stack->setField<int>("DT_BOS", LIBUSB_DT_BOS);
		stack->setField<int>("DT_DEVICE_CAPABILITY", LIBUSB_DT_DEVICE_CAPABILITY);
		stack->setField<int>("DT_HID", LIBUSB_DT_HID);
		stack->setField<int>("DT_REPORT", LIBUSB_DT_REPORT);
		stack->setField<int>("DT_PHYSICAL", LIBUSB_DT_PHYSICAL);
		stack->setField<int>("DT_HUB", LIBUSB_DT_HUB);
		stack->setField<int>("DT_SUPERSPEED_HUB", LIBUSB_DT_SUPERSPEED_HUB);
		stack->setField<int>("DT_SS_ENDPOINT_COMPANION", LIBUSB_DT_SS_ENDPOINT_COMPANION);

		stack->setField<int>("ENDPOINT_IN", LIBUSB_ENDPOINT_IN);
		stack->setField<int>("ENDPOINT_OUT", LIBUSB_ENDPOINT_OUT);

		stack->setField<int>("TRANSFER_TYPE_CONTROL", LIBUSB_TRANSFER_TYPE_CONTROL);
		stack->setField<int>("TRANSFER_TYPE_ISOCHRONOUS", LIBUSB_TRANSFER_TYPE_ISOCHRONOUS);
		stack->setField<int>("TRANSFER_TYPE_BULK", LIBUSB_TRANSFER_TYPE_BULK);
		stack->setField<int>("TRANSFER_TYPE_INTERRUPT", LIBUSB_TRANSFER_TYPE_INTERRUPT);
		stack->setField<int>("TRANSFER_TYPE_BULK_STREAM", LIBUSB_TRANSFER_TYPE_BULK_STREAM);

		stack->setField<int>("ISO_SYNC_TYPE_NONE", LIBUSB_ISO_SYNC_TYPE_NONE);
		stack->setField<int>("ISO_SYNC_TYPE_ASYNC", LIBUSB_ISO_SYNC_TYPE_ASYNC);
		stack->setField<int>("ISO_SYNC_TYPE_ADAPTIVE", LIBUSB_ISO_SYNC_TYPE_ADAPTIVE);
		stack->setField<int>("ISO_SYNC_TYPE_SYNC", LIBUSB_ISO_SYNC_TYPE_SYNC);

		stack->setField<int>("ISO_USAGE_TYPE_DATA", LIBUSB_ISO_USAGE_TYPE_DATA);
		stack->setField<int>("ISO_USAGE_TYPE_FEEDBACK", LIBUSB_ISO_USAGE_TYPE_FEEDBACK);
		stack->setField<int>("ISO_USAGE_TYPE_IMPLICIT", LIBUSB_ISO_USAGE_TYPE_IMPLICIT);

		stack->setField<int>("TRANSFER_SHORT_NOT_OK", LIBUSB_TRANSFER_SHORT_NOT_OK);
		stack->setField<int>("TRANSFER_FREE_BUFFER", LIBUSB_TRANSFER_FREE_BUFFER);
		stack->setField<int>("TRANSFER_FREE_TRANSFER", LIBUSB_TRANSFER_FREE_TRANSFER);
		stack->setField<int>("TRANSFER_ADD_ZERO_PACKET", LIBUSB_TRANSFER_ADD_ZERO_PACKET);

		stack->setField<int>("TRANSFER_COMPLETED", LIBUSB_TRANSFER_COMPLETED);
		stack->setField<int>("TRANSFER_ERROR", LIBUSB_TRANSFER_ERROR);
		stack->setField<int>("TRANSFER_TIMED_OUT", LIBUSB_TRANSFER_TIMED_OUT);
		stack->setField<int>("TRANSFER_CANCELLED", LIBUSB_TRANSFER_CANCELLED);
		stack->setField<int>("TRANSFER_STALL", LIBUSB_TRANSFER_STALL);
		stack->setField<int>("TRANSFER_NO_DEVICE", LIBUSB_TRANSFER_NO_DEVICE);
		stack->setField<int>("TRANSFER_OVERFLOW", LIBUSB_TRANSFER_OVERFLOW);

		//stack->setField<int>("LIBUSB_TRANSFER_COMPLETED", LIBUSB_TRANSFER_COMPLETED);
	}
}

