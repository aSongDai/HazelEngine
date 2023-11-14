
#include "Hazel.h"

#include "glm/glm.hpp"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

//glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
//{
//	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
//	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
//	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
//	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
//	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
//	return Projection * View * Model;
//}

namespace Hazel
{
	class ExampleLayer :public Layer
	{
	public:
		ExampleLayer()
			:Layer("Example"), m_Camera(-1.6f, 1.6f, 0.9f, -0.9f), m_CameraMoveSpeed(0.1f),
			m_CameraPosition(0.0f), m_CameraRotation(0.0f), m_cameraRotationSpeed(1.0f)
		{
			m_VertexArray.reset(VertexArray::Create());

			float vertices[] = {
				-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
				 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
				 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
			};
			m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

			BufferLayout layout = {
				{"a_Position", BufferDataType::Float3},
				{"a_Color", BufferDataType::Float4}
			};
			m_VertexBuffer->SetBufferLayout(layout);
			m_VertexArray->AddVertexBuffer(m_VertexBuffer);


			uint32_t indices[3] = { 0,1,2 };
			m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
			m_VertexArray->SetIndexBuffer(m_IndexBuffer);

			const std::string vertexShaderResource = R"(
		#version 330 core
		layout (location = 0) in vec3 a_Position;
		layout (location = 1) in vec4 a_Color;

		uniform mat4 u_ViewProjectionMatrix;		

		out vec3 v_Position;
		out vec4 v_Color;
		void main()
		{
			v_Position  = a_Position;
			v_Color = a_Color;
			gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
		}
	)";
			const std::string fragmentShaderResource = R"(
		#version 330 core
		layout (location = 0) out vec4 color;
		in vec4 v_Color;
		in vec3 v_Position;
		void main(){
			color = vec4(v_Position + 0.5, 1.0);
			color = v_Color;
		}
	)";
			// Shader
			m_Shader.reset(new Hazel::Shader(vertexShaderResource, fragmentShaderResource));

			// Square Render
			m_SquareVertexArray.reset(VertexArray::Create());
			m_SquareVertexArray->Bind();
			float square_vertices[] = {
				-0.6f, -0.6f, 0.0f,
				 0.6f, -0.6f, 0.0f,
				 0.6f,  0.6f, 0.0f,
				-0.6f,  0.6f, 0.0f
			};
			BufferLayout square_layout =
			{
				{"a_Position", BufferDataType::Float3}
			};
			std::shared_ptr<VertexBuffer> m_SquareVertexBuffer;
			m_SquareVertexBuffer.reset(VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
			m_SquareVertexBuffer->SetBufferLayout(square_layout);
			m_SquareVertexArray->AddVertexBuffer(m_SquareVertexBuffer);
			uint32_t square_indices[] = {
				0,1,2, 2,3,0
			};
			std::shared_ptr<IndexBuffer> m_SquareIndexBuffer;
			m_SquareIndexBuffer.reset(IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(uint32_t)));
			m_SquareVertexArray->SetIndexBuffer(m_SquareIndexBuffer);

			std::string squareVertexShaderSrc = R"(
		#version 330 core
		layout (location = 0) in vec3 a_Position;

		uniform mat4 u_ViewProjectionMatrix;
		void main()
		{
			gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
		}
	)";
			std::string squareFragmentShaderSrc = R"(
		#version 330 core
		layout (location = 0) out vec4 color;
		void main()
		{
			color = vec4(0.2f, 0.3f, 0.8f, 1.0f);
		} 
	)";

			m_SquareShader.reset(new Shader(squareVertexShaderSrc, squareFragmentShaderSrc));

		}

		virtual void OnUpdate() override
		{
			Hazel::RendererCommand::Clear();
			Hazel::RendererCommand::ClearColor({ 0.45f, 0.55f, 0.60f, 1.00f });

			m_Camera.SetPosition(m_CameraPosition);
			m_Camera.SetRotation(m_CameraRotation);
			Hazel::Renderer::BeginScene(m_Camera);

			Hazel::Renderer::Submit(m_SquareVertexArray, m_SquareShader);
			Hazel::Renderer::Submit(m_VertexArray, m_Shader);

			Hazel::Renderer::EndScene();
		}

		virtual void OnImGuiRender() override
		{

		}

		virtual void OnEvent(Hazel::Event& event) override
		{
			EventDispatcher dispatcher(event);
			dispatcher.Dispatch<KeyPressEvent>(HAZEL_BIND_EVENT_FUNCTION(ExampleLayer::OnKeyPressEvent));
		}

		bool OnKeyPressEvent(KeyPressEvent& event)
		{
			if (event.GetKeyCode() == HAZEL_KEY_A)
			{
				m_CameraPosition.x -= m_CameraMoveSpeed;
			}
			if (event.GetKeyCode() == HAZEL_KEY_D)
			{
				m_CameraPosition.x += m_CameraMoveSpeed;
			}
			if (event.GetKeyCode() == HAZEL_KEY_S)
			{
				m_CameraPosition.y -= m_CameraMoveSpeed;
			}
			if (event.GetKeyCode() == HAZEL_KEY_W)
			{
				m_CameraPosition.y += m_CameraMoveSpeed;
			}
			if (event.GetKeyCode() == HAZEL_KEY_LEFT)
			{
				// 
				m_CameraRotation -= m_cameraRotationSpeed;
				
			}
			if (event.GetKeyCode() == HAZEL_KEY_RIGHT)
			{
				m_CameraRotation += m_cameraRotationSpeed;
			}
			return false;
		}

	private:
		std::shared_ptr<Hazel::VertexArray> m_VertexArray;
		std::shared_ptr<Hazel::VertexBuffer> m_VertexBuffer;
		std::shared_ptr<Hazel::IndexBuffer> m_IndexBuffer;
		std::shared_ptr<Hazel::Shader> m_Shader;

		std::shared_ptr<Hazel::VertexArray> m_SquareVertexArray;
		std::shared_ptr<Hazel::Shader> m_SquareShader;

		Hazel::OrthogonalCamera m_Camera;
		glm::vec3 m_CameraPosition;
		float m_CameraRotation;
		float m_cameraRotationSpeed;
		float m_CameraMoveSpeed;
	};
}



class HAZEL_API Sandbox : public Hazel::Application
{
public:
	Sandbox()
		: Hazel::Application()
	{
		PushLayer(new Hazel::ExampleLayer);
	}
	~Sandbox() = default;

private:

};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}
