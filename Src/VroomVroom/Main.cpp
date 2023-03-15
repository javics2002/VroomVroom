#pragma once
#ifndef __VROOMVROOM_MAIN
#define __VROOMVROOM_MAIN

#define DllImport __declspec( dllimport )
#define DllExport __declspec( dllexport )

#include "ComponentsRegister.h"

extern "C" {
	DllExport const char* name() {
		return "Vroom Vroom";
	}
	DllExport void componentsResgister() {
		me::addAllFactory();
	}
}

#endif