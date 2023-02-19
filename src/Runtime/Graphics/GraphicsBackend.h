#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Available graphics backends
	/// </summary>
	enum class PORTAKAL_API GraphicsBackend
	{
		Directx11,
		Directx12,
		Vulkan
	};
}