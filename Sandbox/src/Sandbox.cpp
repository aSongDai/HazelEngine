
#include "Hazel.h"

#include "glm/glm.hpp"



class ExampleLayer :public Hazel::Layer
{
public:
	ExampleLayer() :Layer("Example")
	{
	}
	
	virtual void OnUpdate() override
	{
		//HAZEL_CLIENT_INFO("ExampleLayer::Update");

		if (Hazel::Input::IsKeyPressed(HAZEL_KEY_TAB))
			HAZEL_CLIENT_INFO("Key Table has been pressed!");
	}

	virtual void OnImGuiRender() override
	{
		
	}

	virtual void OnEvent(Hazel::Event& event) override
	{
		//HAZEL_CLIENT_TRACE("{0}", event);
		if (event.GetEventType() == Hazel::EventType::KeyPress)
		{
			Hazel::KeyPressEvent& e = (Hazel::KeyPressEvent&)event;
			HAZEL_CLIENT_TRACE("{0}", (char)e.GetKeyCode());					// 观察这里keycode，强制类型转换之后是溢出的， 所以会出现Control等案件代码与字母重复的情况
		}
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

Hazel::Application* CreateApplication()
{
	return new SandBox();
}