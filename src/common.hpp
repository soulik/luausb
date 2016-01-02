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

#ifndef LUA_USB_COMMON_H
#define LUA_USB_COMMON_H

#include <lutok2/lutok2.hpp>
using namespace lutok2;

#if (BUILDING_LUAUSB || luausb_EXPORTS) && HAVE_VISIBILITY
#define LUAUSB_DLL_EXPORTED __attribute__((visibility("default")))
#elif (BUILDING_LUAUSB || luausb_EXPORTS) && defined _MSC_VER
#define LUAUSB_DLL_EXPORTED __declspec(dllexport)
#elif defined _MSC_VER
#define LUAUSB_DLL_EXPORTED __declspec(dllimport)
#else
#define LUAUSB_DLL_EXPORTED
#endif

#define INIT_OBJECT(OBJ_NAME) state->registerInterface<OBJ_NAME>("luausb_" #OBJ_NAME); state->stack->setField(#OBJ_NAME)
#define OBJECT_IFACE(OBJ_NAME) state.getInterface<OBJ_NAME>("luausb_" #OBJ_NAME)

#include <libusb.h>

#endif