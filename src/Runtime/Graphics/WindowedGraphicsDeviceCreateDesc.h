#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Graphics/GraphicsBackend.h>
#include <Runtime/Graphics/TextureFormat.h>

namespace Portakal
{
	class Window;

	struct PORTAKAL_API WindowedGraphicsDeviceCreateDesc
	{
		Window* pOwnerWindow;
		GraphicsBackend Backend;
		TextureFormat ColorFormat;
		TextureFormat DepthStencilFormat;
		unsigned char BufferCount;
	};
}