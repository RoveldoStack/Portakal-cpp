#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Resource/Material/MaterialParameterType.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/Resource/Sampler/SamplerResource.h>

namespace Portakal
{
	struct PORTAKAL_API MaterialParameterDescriptor
	{
		MaterialParameterType Type;
		GraphicsBuffer* pBuffer;
		unsigned int BufferSizeInBytes;
		ByteBlock BufferData;
		TextureResource* pTexture;
		SamplerResource* pSampler;
	};
}