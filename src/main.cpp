/*
	luausb - Lua binding for usb library

	Copyright 2015 Mário Kašuba

	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are
	met:

	* Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "common.hpp"
#include "init_classes.hpp"

using namespace luausb;

namespace luausb{
	int getErrorName(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			const char * text = libusb_error_name(stack->to<int>(1));
			stack->push<const std::string &>(text);
			return 1;
		}
		else{
			return 0;
		}
	}

	int getStrError(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			const char * text = libusb_strerror(static_cast<libusb_error>(stack->to<int>(1)));
			stack->push<const std::string &>(text);
			return 1;
		}
		else{
			return 0;
		}
	}

	int hasCapability(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			stack->push<bool>(libusb_has_capability(stack->to<int>(1)));
			return 1;
		}
		return 0;
	}

	int getVersion(State & state){
		Stack * stack = state.stack;
		const libusb_version * version = libusb_get_version();
		stack->newTable();
		{
			stack->setField<int>("major", version->major);
			stack->setField<int>("minor", version->minor);
			stack->setField<int>("micro", version->micro);
			stack->setField<int>("nano", version->nano);
			stack->setField<const std::string &>("rc", version->rc);
			stack->setField<const std::string &>("describe", version->describe);
		}
		
		return 1;
	}

	int setLocale(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1)){
			const std::string localeName = stack->to<const std::string>(1);
			int result = 0;
			if ((result = libusb_setlocale(localeName.c_str())) == LIBUSB_SUCCESS){
				stack->push<bool>(true);
			}
			else{
				stack->push<int>(result);
			}
			return 1;
		}
		return 0;
	}

	int getSupportedLocales(State & state){
		const char * usbi_locale_supported[] = { "en", "nl", "fr", "ru" };
		Stack * stack = state.stack;
		stack->newTable();
		size_t elements = (sizeof(usbi_locale_supported) / sizeof(usbi_locale_supported[0]));
		for (size_t i = 0; i < elements; i++){
			stack->push<int>(i+1);
			stack->push<const std::string &>(usbi_locale_supported[i]);
			stack->setTable();
		}
		return 1;
	}
}

extern "C" LUAUSB_DLL_EXPORTED int luaopen_luausb(lua_State * L){
	State * state = new State(L);
	Stack * stack = state->stack;
	Module luausb_module;

	stack->newTable();

	initConstants(state, luausb_module);
	initContext(state, luausb_module);
	initDevice(state, luausb_module);
	initDeviceHandle(state, luausb_module);
	initInterface(state, luausb_module);
	initTransfer(state, luausb_module);

	initBosDescriptor(state, luausb_module);
	initBosDevCapabilityDescriptor(state, luausb_module);
	initConfigDescriptor(state, luausb_module);
	initContainerIDDescriptor(state, luausb_module);
	initControlSetup(state, luausb_module);
	initDeviceDescriptor(state, luausb_module);
	initEndpointDescriptor(state, luausb_module);
	initInterfaceDescriptor(state, luausb_module);
	initISOPacketDescriptor(state, luausb_module);
	initUSB20ExtensionDescriptor(state, luausb_module);
	initSSUSBDeviceCapabilityDescriptor(state, luausb_module);
	initSSEndpointCompanionDescriptor(state, luausb_module);

	luausb_module["getErrorString"] = getErrorName;
	luausb_module["getStrError"] = getStrError;
	luausb_module["getVersion"] = getVersion;
	luausb_module["hasCapability"] = hasCapability;
	luausb_module["setLocale"] = setLocale;
	luausb_module["getSupportedLocales"] = getSupportedLocales;

	state->registerLib(luausb_module);
	return 1;
}

