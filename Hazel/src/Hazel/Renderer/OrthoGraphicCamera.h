#pragma once
#include "Hazel/Camera.h"

namespace Hazel
{
	class OrthoGraphicCamera :public Camera
	{
	public:
		OrthoGraphicCamera(float left, float right, float bottom, float top);

		virtual void SetRotation(float rotation) override 
		{
			m_Rotation = rotation;
			ReCalculateViewProjectionMatrix();
		}

		virtual void SetPosition(const glm::vec3& position) override
		{
			m_Position = position;
			ReCalculateViewProjectionMatrix();
		}

		virtual glm::mat4 GetViewProjectionMatrix() const override {
			return m_ViewProjectionMatrix;
		}

		void ReCalculateViewProjectionMatrix();

	private:
		glm::mat4	m_ViewMatrix;
		glm::mat4	m_ProjectionMatrix;
		glm::mat4	m_ViewProjectionMatrix;

		float		m_Rotation = 0.0f;
		glm::vec3	m_Position = {0.0f, 0.0f, 0.0f};
	};
}