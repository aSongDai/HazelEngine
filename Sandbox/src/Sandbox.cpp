
#include "Hazel.h"



class ExampleLayer :public Hazel::Layer
{
public:
	ExampleLayer() :Layer("Example")
	{

	}
	
	void OnUpdate() override
	{
		//HAZEL_CLIENT_INFO("ExampleLayer::Update");

		if (Hazel::Input::IsKeyPressed(HAZEL_KEY_TAB))
			HAZEL_CLIENT_INFO("Key Table has been pressed!");
	}

	void OnEvent(Hazel::Event& event) override
	{
		//HAZEL_CLIENT_TRACE("{0}", event);
		if (event.GetEventType() == Hazel::EventType::KeyPress)
		{
			Hazel::KeyPressEvent& e = (Hazel::KeyPressEvent&)event;
			HAZEL_CLIENT_TRACE("{0}", (char)e.GetKeyCode());					// �۲�����keycode��ǿ������ת��֮��������ģ� ���Ի����Control�Ȱ�����������ĸ�ظ������
		}
	}
};


class SandBox : public Hazel::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Hazel::ImGuiLayer);
	}
	~SandBox() = default;
};

Hazel::Application* Hazel::CreateApplication()
{
	return new SandBox();
}