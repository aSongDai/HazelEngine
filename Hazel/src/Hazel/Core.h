#pragma once



#ifdef HAZEL_PLATFORM_WINDOWS

#if HAZEL_DYNAMIC_LINK
#ifdef HAZEL_BUILD_DLL
	#define HAZEL_API __declspec(dllexport)
#else
	#define HAZEL_API __declspec(dllimport)
#endif						// HAZEL_BUILD_DLL
#else
#define HAZEL_API
#endif						// HAZEL_DYNAMIC_LINK

#else
	#error Hazel only support Windows!
#endif // 

#ifndef HAZEL_LOG
#define HAZEL_LOG 
#include "Hazel/HazelLog.h"
#endif // !HAZEL_LOG

#ifdef HAZEL_DEBUG
#define HAZEL_ENABLE_ASSERTS
#elif
#define HAZEL_ENABLE_ASSERTS
#endif

#define HAZEL_ENABLE_ASSERTS 1

#ifdef HAZEL_ENABLE_ASSERTS
	#define HAZEL_CLIENT_ASSERT(x, ...)		{ if(!(x)) {HAZEL_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define HAZEL_CORE_ASSERT(x, ...)		{ if(!(x)) {HAZEL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define HAZEL_CLIENT_ASSERT(x, ...)
	#define HAZEL_CORE_ASSERT(x, ...)
#endif						// HAZEL_ENABLE_ASSERTS


#define BIT(x) (1 << x)

// bind the callback function
#define HAZEL_BIND_EVENT_FUNCTION(function) std::bind(&function, this, std::placeholders::_1)