#pragma once
#include "Hazel/Core.h"

namespace Hazel
{
	class HAZEL_API GraphicContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;
	private:

	};
}