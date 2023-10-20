
#include "Hazel.h"

#include "glm/glm.hpp"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}


class ExampleLayer :public Hazel::Layer
{
public:
	ExampleLayer() :Layer("Example")
	{
		auto cam = camera(5.0f, { 0.5f,0.5f });
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
	}
	~SandBox() = default;
};

Hazel::Application* Hazel::CreateApplication()
{
	return new SandBox();
}