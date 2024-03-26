#pragma once
#include "Core.h"
#include "Renderer/OrthographicCamera.h"
#include "Hazel/Core/TimeStep.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"	

namespace Hazel
{

	/*
		
	*/
	class HAZEL_API OrthographicCameraController
	{
	public:
		OrthographicCameraController() = default;
		OrthographicCameraController(float aspectRatio, bool rotation);						// 纵横比, 设置正交相机的纵横比
		virtual ~OrthographicCameraController() = default;

		inline OrthographicCamera& GetCamera() { return m_Camera; }
		inline const OrthographicCamera& GetCamera() const { return m_Camera; }

		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);
	private:
		bool OnMouseScrolled(MouseScrollEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		float m_AspectRatio;				// 纵横比
		float m_ZoomLevel = 1.0f;			// 缩放级别
		bool m_Rotation;					// TOEXPLEAN::
		OrthographicCamera m_Camera;

		float m_CameraTranslationSpeed = 1.0f, m_CameraRotationSpeed = 45.0f;

		// status of camera 
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
	};

}