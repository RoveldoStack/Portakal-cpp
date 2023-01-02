#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	enum class PORTAKAL_API GraphicsBackend
	{
		OpenGL,
		OpenGLES,
		Directx11,
		Directx12,
		Vulkan,
		Metal
	};
}