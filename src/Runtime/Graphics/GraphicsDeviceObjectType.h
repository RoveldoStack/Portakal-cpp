#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	enum class PORTAKAL_API GraphicsDeviceObjectType
	{
		Framebuffer,
		Buffer,
		Texture,
		Sampler,
		Shader,
		ResourceTable,
		CommandList,
		Pipeline,
		Swapchain
	};
}