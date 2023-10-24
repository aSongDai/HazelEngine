#pragma once


namespace Hazel
{
	enum class RenderEnum
	{
		None		=	0,
		OpenGLAPI	=	1,
		// DirectX	=	2,						// ���ڿ��Ը�����Ҫ���
	};

	class RenderAPI
	{
	public:
		inline static RenderEnum GetAPI() { return s_RendererAPI; }
	private:
		static RenderEnum s_RendererAPI;
	};
}