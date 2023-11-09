#pragma once

#include "Hazel/Core.h"

#include <glm/glm.hpp>


/*
	glsl�е����������еģ� �任��Ҫ�۳˵ľ���˳���ǣ�����������˵�Ĳ�һ������Ҫ����OpenGLԴ����˵��
		projectionMatrix * viewMatrix * modelMatrix * VertexPosition
	�����������DirectX�������෴
		vertexPosition * modelMatrix * viewMatrix * projectionMatrix
*/
namespace Hazel
{
	class HAZEL_API OrthogonalCamera
	{
	public:
		OrthogonalCamera(float left, float right, float top, float bottom);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix();}
		const float GetRotation() const { return m_Rotation; }
		void SetRotation(const float& rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		inline const auto& GetViewMatrix() { return m_ViewMatrix; }
		inline const auto& GetProjectionMatrix() { return m_ProjectionMatrix; }
		inline const auto& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();											// ���� position ���� rotation �ȵ�ʱ����Ҫ���¼�����ͼ����

	private:
		// �����ʵ���Ǵ洢�任����ľ�������������Ҫ��Ⱦ�������Ƿ�Ҫ����Ļ����Ⱦ����

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f,0.0f };
		float m_Rotation = 0.0f;												// 2D��Ⱦ��������һ���������ת

	};
}