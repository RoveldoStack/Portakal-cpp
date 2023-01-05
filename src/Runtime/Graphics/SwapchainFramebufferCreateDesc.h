#pragma once
#include <Runtime/Graphics/TextureFormat.h>

namespace Portakal
{
	struct PORTAKAL_API SwapchainFramebufferCreateDesc
	{
		TextureFormat ColorFormat;
		TextureFormat DepthStencilFormat;
		unsigned int Width;
		unsigned int Height;
		unsigned int BufferCount;
	};
}