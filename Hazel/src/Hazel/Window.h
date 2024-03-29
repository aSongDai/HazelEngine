#pragma once

#include "Events/Event.h"
#include "Core.h"
#include "Hazel/Renderer/GraphicContext.h"

#include <string>
#include <functional>

namespace Hazel
{
	using EventCallbackFunction = std::function<void(Event&)>;

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Hazel Engine Window",
			unsigned int width=1280,
			unsigned int height=720):Title(title),Width(width),Height(height){}
	};
	 

	/*
		Interface representing a desktop system based Window.
	*/
	class HAZEL_API Window
	{
	public:

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

	public:													// static function
		static Window* Create(const WindowProps& props = WindowProps());
	public:
		GraphicContext* m_GraphicContext;

	private:
		unsigned int m_width, m_height;
	};
}