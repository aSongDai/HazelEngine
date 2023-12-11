
#include "Hazel.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Hazel/vendor/imgui/imgui.h>

//glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
//{
//	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
//	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
//	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
//	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
//	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
//	return Projection * View * Model;
//}


class ExampleLayer :public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, 0.9f, -0.9f), m_CameraMoveSpeed(1.0f),
		m_CameraPosition(0.0f), m_CameraRotation(0.0f), m_cameraRotationSpeed(10.f),
		m_ProjectPosition(glm::vec3(1.0f))
	{
		m_VertexArray.reset(Hazel::VertexArray::Create());

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
				0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
				0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		m_VertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));

		Hazel::BufferLayout layout = {
			{"a_Position", Hazel::BufferDataType::Float3},
			{"a_Color", Hazel::BufferDataType::Float4}
		};
		m_VertexBuffer->SetBufferLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);


		uint32_t indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		const std::string vertexShaderResource = R"(
			#version 330 core
			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;	
			uniform mat4 u_TransformMatrix;	

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position  = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * u_TransformMatrix * vec4(a_Position, 1.0);
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
		m_Shader.reset(Hazel::Shader::Create(vertexShaderResource, fragmentShaderResource));

		// Square Render
		m_SquareVertexArray.reset(Hazel::VertexArray::Create());
		m_SquareVertexArray->Bind();
		float square_vertices[] = {
			-0.6f, -0.6f, 0.0f,
				0.6f, -0.6f, 0.0f,
				0.6f,  0.6f, 0.0f,
			-0.6f,  0.6f, 0.0f
		};
		Hazel::BufferLayout square_layout =
		{
			{"a_Position", Hazel::BufferDataType::Float3}
		};
		std::shared_ptr<Hazel::VertexBuffer> m_SquareVertexBuffer;
		m_SquareVertexBuffer.reset(Hazel::VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
		m_SquareVertexBuffer->SetBufferLayout(square_layout);
		m_SquareVertexArray->AddVertexBuffer(m_SquareVertexBuffer);
		uint32_t square_indices[] = {
			0,1,2, 2,3,0
		};
		std::shared_ptr<Hazel::IndexBuffer> m_SquareIndexBuffer;
		m_SquareIndexBuffer.reset(Hazel::IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(m_SquareIndexBuffer);

		std::string squareVertexShaderSrc = R"(
			#version 330 core
			layout (location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_TransformMatrix;
			void main()
			{
				gl_Position = u_ViewProjectionMatrix * u_TransformMatrix * vec4(a_Position, 1.0);
			}
		)";
		std::string squareFragmentShaderSrc = R"(
			#version 330 core
			layout (location = 0) out vec4 color;

			uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color, 1.0f);
			} 
		)";

		m_SquareShader.reset(Hazel::Shader::Create(squareVertexShaderSrc, squareFragmentShaderSrc));


		// redColorShader
		std::string redVertexShaderSrc = R"(
			#version 330 core
			layout (location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_TransformMatrix;
			void main()
			{
				gl_Position = u_ViewProjectionMatrix * u_TransformMatrix * vec4(a_Position, 1.0);
			}
		)";
		std::string redFragmentShaderSrc = R"(
			#version 330 core
			layout (location = 0) out vec4 color;
			void main()
			{
				color = vec4(0.8f, 0.2f, 0.3f, 1.0f);
			} 
		)";
		m_RedColorShader.reset(Hazel::Shader::Create(redVertexShaderSrc, redFragmentShaderSrc));

		// blueColorShader
		std::string blueVertexShaderSrc = R"(
			#version 330 core
			layout (location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_TransformMatrix;
			void main()
			{
				gl_Position = u_ViewProjectionMatrix * u_TransformMatrix * vec4(a_Position, 1.0);
			}
		)";
		std::string blueFragmentShaderSrc = R"(
			#version 330 core
			layout (location = 0) out vec4 color;
			void main()
			{
				color = vec4(0.2f, 0.3f, 0.8f, 1.0f);
			} 
		)";
		m_BlueColorShader.reset(Hazel::Shader::Create(blueVertexShaderSrc, blueFragmentShaderSrc));
	}

	virtual void OnUpdate(Hazel::TimeStep& deltaTime) override
	{
		//HAZEL_CLIENT_TRACE("TimeStep: {0}s \t {1}ms", deltaTime.GetTime(), deltaTime.GetMilliSecond());
		if (Hazel::Input::IsKeyPressed(HAZEL_KEY_A))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * deltaTime;
		}
		if (Hazel::Input::IsKeyPressed(HAZEL_KEY_D))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * deltaTime;
		}
		if (Hazel::Input::IsKeyPressed(HAZEL_KEY_S))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * deltaTime;
		}
		if (Hazel::Input::IsKeyPressed(HAZEL_KEY_W))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * deltaTime;
		}
		if (Hazel::Input::IsKeyPressed(HAZEL_KEY_LEFT))
		{
			m_CameraRotation -= m_cameraRotationSpeed * deltaTime;
		}
		if (Hazel::Input::IsKeyPressed(HAZEL_KEY_RIGHT))
		{
			m_CameraRotation += m_cameraRotationSpeed * deltaTime;
		}

		if (Hazel::Input::IsKeyPressed(HAZEL_KEY_J))
		{
			m_ProjectPosition.x -= m_CameraMoveSpeed * deltaTime;
		}
		if (Hazel::Input::IsKeyPressed(HAZEL_KEY_L))
		{
			m_ProjectPosition.x += m_CameraMoveSpeed * deltaTime;
		}
		if (Hazel::Input::IsKeyPressed(HAZEL_KEY_K))
		{
			m_ProjectPosition.y -= m_CameraMoveSpeed * deltaTime;
		}
		if (Hazel::Input::IsKeyPressed(HAZEL_KEY_I))
		{
			m_ProjectPosition.y += m_CameraMoveSpeed * deltaTime;
		}


		Hazel::RendererCommand::Clear();
		Hazel::RendererCommand::ClearColor({ 0.45f, 0.55f, 0.60f, 1.00f });

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		Hazel::Renderer::BeginScene(m_Camera);

		
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_SquareShader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_SquareShader)->UploadUniformFloat3("u_Color", m_SquareColor);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_ProjectPosition);
		Hazel::Renderer::Submit(m_SquareVertexArray, m_SquareShader, transform);
		
		Hazel::Renderer::Submit(m_VertexArray, m_Shader);

		Hazel::Renderer::EndScene();


	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();
	}

	virtual void OnEvent(Hazel::Event& event) override
	{
	}

private:
	std::shared_ptr<Hazel::VertexArray> m_VertexArray;
	std::shared_ptr<Hazel::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Hazel::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Hazel::Shader> m_Shader;
	std::shared_ptr<Hazel::VertexArray> m_SquareVertexArray;
	std::shared_ptr<Hazel::Shader> m_SquareShader;

	// Test
	std::shared_ptr<Hazel::Shader> m_RedColorShader;
	std::shared_ptr<Hazel::Shader> m_BlueColorShader;

	Hazel::OrthogonalCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation;
	float m_cameraRotationSpeed;
	float m_CameraMoveSpeed;

	glm::vec3 m_ProjectPosition;
	glm::vec3 m_SquareColor;
};



class HAZEL_API Sandbox : public Hazel::Application
{
public:
	Sandbox()
		: Hazel::Application()
	{
		PushLayer(new ExampleLayer);
	}
	~Sandbox() = default;

private:

};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}
