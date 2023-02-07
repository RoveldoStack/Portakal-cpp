#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	enum class PORTAKAL_API PipelineResourceType
	{
        ConstantBuffer,
        StructuredBufferReadOnly,
        StructuredBufferReadWrite,
        TextureReadOnly,
        TextureReadWrite,
        Sampler
	};
}