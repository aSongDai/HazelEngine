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
		OrthographicCameraController(float aspectRatio, bool rotation);						// �ݺ��, ��������������ݺ��
		virtual ~OrthographicCameraController() = default;

		inline OrthographicCamera& GetCamera() { return m_Camera; }
		inline const OrthographicCamera& GetCamera() const { return m_Camera; }

		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);
	private:
		bool OnMouseScrolled(MouseScrollEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		float m_AspectRatio;				// �ݺ��
		float m_ZoomLevel = 1.0f;			// ���ż���
		bool m_Rotation;					// TOEXPLEAN::
		OrthographicCamera m_Camera;

		float m_CameraTranslationSpeed = 1.0f, m_CameraRotationSpeed = 45.0f;

		// status of camera 
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
	};

}