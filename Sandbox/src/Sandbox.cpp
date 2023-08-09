

#include "Hazel.h"

class ExampleLayer :public Hazel::Layer
{
public:
	ExampleLayer() :Layer("Example")
	{

	}
	
	void OnUpdate() override
	{
		HAZEL_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Hazel::Event& event) override
	{
		HAZEL_CLIENT_TRACE("{0}", event);
	}
};


class SandBox : public Hazel::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
	}
	~SandBox() = default;
};

Hazel::Application* Hazel::CreateApplication()
{
	return new SandBox();
}