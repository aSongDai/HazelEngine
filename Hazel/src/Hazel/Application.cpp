#include "Hazelpch.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "HazelLog.h"


Hazel::Application::Application()
{
}

Hazel::Application::~Application()
{
}

void Hazel::Application::Run()
{

	WindowResizeEvent e(1280, 720);
	HAZEL_CLIENT_TRACE(e);
	
	while (true);
}
