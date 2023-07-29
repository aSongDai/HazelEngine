#pragma once

extern Hazel::Application* Hazel::CreateApplication();

#ifdef HAZEL_PLATFORM_WINDOWS

int main(int* argc,char** argv)
{
	// Test the Log system
	Hazel::Log::Init();
	HAZEL_CORE_WARN("initial the Hazel Engine;");
	HAZEL_CLIENT_INFO("Initial the App!");

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif // HAZEL_PLATFORM_WINDOWS
