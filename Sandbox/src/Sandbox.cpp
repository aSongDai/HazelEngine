
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
		:Layer("Example"), m_CameraController(1.6f / 0.9f, true),
		m_ProjectPosition(glm::vec3(0.f)), m_SquareColor(glm::vec3(0.5f, 0.1f, 0.6f))
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
		m_Shader = Hazel::Shader::Create("positionColorShader",vertexShaderResource, fragmentShaderResource);

		// Square Render
		m_SquareVertexArray.reset(Hazel::VertexArray::Create());
		m_SquareVertexArray->Bind();
		float square_vertices[] = {
			   -0.6f, -0.6f, 0.0f, 0.0f, 0.0f,
				0.6f, -0.6f, 0.0f, 1.0f, 0.0f,
				0.6f,  0.6f, 0.0f, 1.0f, 1.0f,
			   -0.6f,  0.6f, 0.0f, 0.0f, 1.0f
		};
		Hazel::BufferLayout square_layout =
		{
			{"a_Position", Hazel::BufferDataType::Float3},
			{"a_TexCoord", Hazel::BufferDataType::Float2}
		};
		Hazel::Ref<Hazel::VertexBuffer> m_SquareVertexBuffer;
		m_SquareVertexBuffer.reset(Hazel::VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
		m_SquareVertexBuffer->SetBufferLayout(square_layout);
		m_SquareVertexArray->AddVertexBuffer(m_SquareVertexBuffer);
		uint32_t square_indices[] = {
			0,1,2, 2,3,0
		};
		Hazel::Ref<Hazel::IndexBuffer> m_SquareIndexBuffer;
		m_SquareIndexBuffer.reset(Hazel::IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(m_SquareIndexBuffer);

		// Square Shader
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

		m_SquareShader = Hazel::Shader::Create("squareShader", squareVertexShaderSrc, squareFragmentShaderSrc);


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
		m_RedColorShader = (Hazel::Shader::Create("redShader", redVertexShaderSrc, redFragmentShaderSrc));

		// blueColorShader
		std::string blueVertexShaderSrc = R"(
			#version 330 core
			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_TransformMatrix;

			out vec2 v_TexCoord;
			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjectionMatrix * u_TransformMatrix * vec4(a_Position, 1.0);
			}
		)";
		std::string blueFragmentShaderSrc = R"(
			#version 330 core
			layout (location = 0) out vec4 color;

			in vec2 v_TexCoord;
			void main()
			{
				color = vec4(v_TexCoord, 0.0f, 1.0f);
			} 
		)";
		m_BlueColorShader = (Hazel::Shader::Create("blueShader", blueVertexShaderSrc, blueFragmentShaderSrc));


		auto textureShader = m_ShaderLibrary.LoadShader("src/asserts/shaders/Texture.glsl");

		//m_TextureShader.reset(Hazel::Shader::Create(textureVertexShaderRes, textureFragmentShaderRes));
		
		m_Texture = (Hazel::Texture2D::Create("src/asserts/textures/Checkerboard.png"));
		//m_LogoTexture = Hazel::Texture2D::Create("src/asserts/textures/test.png");
		m_LogoTexture = Hazel::Texture2D::Create("src/asserts/textures/ChernoLogo.png");
		//// upload texture
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	virtual void OnUpdate(Hazel::TimeStep& deltaTime) override
	{
		// Update camera.
		m_CameraController.OnUpdate(deltaTime);

		// Renderer 
		Hazel::RendererCommand::Clear();
		Hazel::RendererCommand::ClearColor({ 0.45f, 0.55f, 0.60f, 1.00f });

		Hazel::Renderer::BeginScene(m_CameraController.GetCamera());

		m_Texture->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_SquareShader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_SquareShader)->UploadUniformFloat3("u_Color", m_SquareColor);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_ProjectPosition);
		Hazel::Renderer::Submit(m_SquareVertexArray, m_ShaderLibrary.GetShader("Texture"), transform);

		// logo texture
		m_LogoTexture->Bind();
		Hazel::Renderer::Submit(m_SquareVertexArray, m_ShaderLibrary.GetShader("Texture"), transform);
		

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
		m_CameraController.OnEvent(event);
	}

private:
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;
	Hazel::Ref<Hazel::VertexBuffer> m_VertexBuffer;
	Hazel::Ref<Hazel::IndexBuffer> m_IndexBuffer;
	Hazel::Ref<Hazel::Shader> m_Shader;
	Hazel::Ref<Hazel::VertexArray> m_SquareVertexArray;
	Hazel::Ref<Hazel::Shader> m_SquareShader;

	// Test
	Hazel::Ref<Hazel::Shader> m_RedColorShader;
	Hazel::Ref<Hazel::Shader> m_BlueColorShader;
	//Hazel::Ref<Hazel::Shader> m_TextureShader;

	Hazel::Ref<Hazel::Texture2D> m_Texture, m_LogoTexture;

	Hazel::ShaderLibrary m_ShaderLibrary;
	

	// Hazel::OrthographicCamera m_Camera;
	Hazel::OrthographicCameraController m_CameraController;

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
