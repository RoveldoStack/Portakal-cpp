#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Available graphics device objects
	/// </summary>
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
		Swapchain,
		Fence
	};
}