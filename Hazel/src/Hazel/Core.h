#pragma once


#include <memory>

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

#ifdef HAZEL_DEBUG
#define HAZEL_ENABLE_ASSERTS
#endif

#define HAZEL_ENABLE_ASSERTS 1
#include "Hazel/HazelLog.h"

#if HAZEL_ENABLE_ASSERTS
	#define HAZEL_CLIENT_ASSERT(x, ...)		{ if(!(x)) {HAZEL_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define HAZEL_CORE_ASSERT(x, ...)		{ if(!(x)) {HAZEL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define HAZEL_CLIENT_ASSERT(x, ...)
	#define HAZEL_CORE_ASSERT(x, ...)
#endif						// HAZEL_ENABLE_ASSERTS


#define BIT(x) (1 << x)

// bind the callback function
#define HAZEL_BIND_EVENT_FUNCTION(function) std::bind(&function, this, std::placeholders::_1)


namespace Hazel
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}