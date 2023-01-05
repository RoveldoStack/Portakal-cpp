#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	enum class PORTAKAL_API GraphicsResourceType
	{
        UniformBuffer,
        StructuredBufferReadOnly,
        StructuredBufferReadWrite,
        TextureReadOnly,
        TextureReadWrite,
        Sampler
	};
}