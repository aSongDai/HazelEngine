#pragma once


#ifdef HAZEL_PLATFORM_WINDOWS

#ifdef HAZEL_BUILD_DLL
#define HAZEL_API __declspec(dllexport)
#else
#define HAZEL_API __declspec(dllimport)
#endif // HAZEL_BUILD_DLL
#else
#error Hazel only support Windows!
#endif // 

#define BIT(x) (1 << x)
