#pragma once
#include "Hazel/Core.h"


#include <glm/glm.hpp>
namespace Hazel
{

	class Camera
	{
	public:
		virtual void SetPosition(const glm::vec3& position) = 0;
		virtual void SetRotation(float rotation) = 0;

		virtual glm::mat4 GetViewProjectionMatrix() const = 0;
	};

}