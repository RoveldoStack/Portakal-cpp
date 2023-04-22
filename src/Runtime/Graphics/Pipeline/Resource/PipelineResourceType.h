#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Available resource types which is commitable to the pipeline
	/// </summary>
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