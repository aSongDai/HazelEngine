#pragma once

#include "Hazel/Core.h"

#include <glm/glm.hpp>


/*
	glsl中的向量是主行的， 变换需要累乘的矩阵顺序是：（这里两集说的不一样，需要看看OpenGL源码再说）
		projectionMatrix * viewMatrix * modelMatrix * VertexPosition
	而这种情况在DirectX中正好相反
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
		void RecalculateViewMatrix();											// 设置 position 或者 rotation 等的时候需要重新计算视图矩阵

	private:
		// 相机其实就是存储变换矩阵的矩阵，用来计算需要渲染的物体是否要在屏幕中渲染出来

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f,0.0f };
		float m_Rotation = 0.0f;												// 2D渲染，仅仅做一个方向的旋转

	};
}