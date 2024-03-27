#include "OrthoCameraController.h"	

#include "Hazel/Input.h"
#include "Hazel/KeyCode.h"


namespace Hazel
{

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio), m_Rotation(rotation), m_Camera(- m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel)
	{
		
	}

	void OrthographicCameraController::OnUpdate(TimeStep timeStep)
	{
		// transform
		if (Input::IsKeyPressed(HAZEL_KEY_A))
		{
			m_CameraPosition.x -= m_CameraTranslationSpeed * timeStep;
		}
		if (Input::IsKeyPressed(HAZEL_KEY_D))
		{
			m_CameraPosition.x += m_CameraTranslationSpeed * timeStep;
		}
		if (Input::IsKeyPressed(HAZEL_KEY_W))
		{
			m_CameraPosition.y -= m_CameraTranslationSpeed * timeStep;
		}
		if (Input::IsKeyPressed(HAZEL_KEY_S))
		{
			m_CameraPosition.y += m_CameraTranslationSpeed * timeStep;
		}

		// rotate
		if (m_Rotation)
		{ 
			if (Input::IsKeyPressed(HAZEL_KEY_Q))
			{
				m_CameraRotation -= m_CameraRotationSpeed * timeStep;
			}
			if (Input::IsKeyPressed(HAZEL_KEY_E))
			{
				m_CameraRotation += m_CameraRotationSpeed * timeStep;
			}
			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseScrollEvent>(HAZEL_BIND_EVENT_FUNCTION(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(HAZEL_BIND_EVENT_FUNCTION(OrthographicCameraController::OnWindowResize));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrollEvent& e)
	{
		m_ZoomLevel -= e.GetYoffset() * 0.5f;

		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();

		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel);

		return false;
	}


}