#pragma once


namespace Hazel
{
	enum class RenderEnum
	{
		None		=	0,
		OpenGLAPI	=	1,
		// DirectX	=	2,						// 后期可以根据需要相加
	};

	class RenderAPI
	{
	public:
		inline static RenderEnum GetAPI() { return s_RendererAPI; }
	private:
		static RenderEnum s_RendererAPI;
	};
}