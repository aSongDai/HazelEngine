#include "ImGuiLayer.h"	
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
//#include "Platform/OpenGL/imgui_impl_glfw.h"
#include "Hazel/Application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
namespace Hazel
{

	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		
		// Set the KeyCode
		// ...
		io.KeyMap[ImGuiKey_Tab]				= GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow]		= GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow]		= GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow]			= GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow]		= GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp]			= GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown]		= GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home]			= GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End]				= GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert]			= GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete]			= GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace]		= GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space]			= GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter]			= GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape]			= GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A]				= GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C]				= GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V]				= GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X]				= GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y]				= GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z]				= GLFW_KEY_Z;


		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate()
	{
		// Set Display Size
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		// Set delta time
		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		// 使用imgui开启一个新帧
		/*ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();*/
		ImGui_ImplOpenGL3_NewFrame();
		//ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();					// The exception is there now.

		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		
		ImGui::Render();
		//glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressEvent>(HAZEL_BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseButtenPressedEvent));
		dispatcher.Dispatch<MouseButtonReleaseEvent>(HAZEL_BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseReleasedEvent));
		dispatcher.Dispatch<MouseMoveEvent>(HAZEL_BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseMoveEvent));
		dispatcher.Dispatch<MouseScrollEvent>(HAZEL_BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseScrollEvent));
		dispatcher.Dispatch<KeyPressEvent>(HAZEL_BIND_EVENT_FUNCTION(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleaseEvent>(HAZEL_BIND_EVENT_FUNCTION(ImGuiLayer::OnKeyReleaseEvent));
		dispatcher.Dispatch<KeyTypeEvent>(HAZEL_BIND_EVENT_FUNCTION(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(HAZEL_BIND_EVENT_FUNCTION(ImGuiLayer::OnWindowResize));
		
		
	}

	bool ImGuiLayer::OnMouseButtenPressedEvent(MouseButtonPressEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;

	}

	bool ImGuiLayer::OnMouseReleasedEvent(MouseButtonReleaseEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false; 

		return false;

	}

	bool ImGuiLayer::OnMouseMoveEvent(MouseMoveEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrollEvent(MouseScrollEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXoffset();
		io.MouseWheel += e.GetYoffset();
		
		return false;

	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return false;
	}

	bool ImGuiLayer::OnKeyReleaseEvent(KeyReleaseEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
		{
			io.AddInputCharacter((unsigned short)keycode);
		}

		return false;
	}

	bool ImGuiLayer::OnWindowResize(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
		return false;
	}

}