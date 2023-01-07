#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	enum class PORTAKAL_API GraphicsResourceType
	{
        ConstantBuffer,
        StructuredBufferReadOnly,
        StructuredBufferReadWrite,
        TextureReadOnly,
        TextureReadWrite,
        Sampler
	};
}