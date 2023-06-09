#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Resource/Material/MaterialParameterType.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/Resource/Sampler/SamplerResource.h>
#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>
namespace Portakal
{
	struct PORTAKAL_API MaterialParameterDescriptor
	{
		MaterialParameterDescriptor() : pTexture(nullptr),pSampler(nullptr),pBuffer(nullptr),pBufferData(nullptr),BufferSizeInBytes(0),Type(MaterialParameterType::Buffer) {}
		~MaterialParameterDescriptor() = default;
		MaterialParameterType Type;
		TextureResource* pTexture;
		SamplerResource* pSampler;
		GraphicsBuffer* pBuffer;
		void* pBufferData;
		unsigned int BufferSizeInBytes;
	};
}