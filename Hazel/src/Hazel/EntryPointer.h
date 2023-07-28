#pragma once
#include "Application.h"

extern Hazel::Application* Hazel::CreateApplication();

#ifdef HAZEL_PLATFORM_WINDOWS

int main(int* argc,char** argv)
{
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif // HAZEL_PLATFORM_WINDOWS
