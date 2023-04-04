#pragma once
#ifndef __VROOMVROOM_VROOMVROOM
#define __VROOMVROOM_VROOMVROOM

#define __VROOMVROOM_EXPORT
#ifdef __VROOMVROOM_EXPORT
#define __VROOMVROOM_API __declspec(dllexport)
#else
#define __VROOMVROOM_API __declspec(dllimport)
#endif

extern "C" {
	__VROOMVROOM_API const char* name();

	__VROOMVROOM_API bool init();

	__VROOMVROOM_API void initFactories();

	__VROOMVROOM_API void initInput();
}

#endif