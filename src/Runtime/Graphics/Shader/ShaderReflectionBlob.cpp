#include "ShaderReflectionBlob.h"
#include <Runtime/HLSL/DX11HLSLShaderReflectionBlob.h>
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	ShaderReflectionBlob* ShaderReflectionBlob::Create(const ByteBlock& byteBlock, GraphicsBackend backend)
	{
		ShaderReflectionBlob* pBlob = nullptr;
		switch (backend)
		{
			case Portakal::GraphicsBackend::Directx11:
			{
				pBlob = new DX11HLSLShaderReflectionBlob(byteBlock);
				break;
			}
			case Portakal::GraphicsBackend::Directx12:
				break;
			case Portakal::GraphicsBackend::Vulkan:
				break;
			case Portakal::GraphicsBackend::Gnm:
				break;
			case Portakal::GraphicsBackend::Nvn:
				break;
			default:
				break;
		}

		ASSERT(pBlob != nullptr, "ShaderReflectionBlob", "Failed to create ShaderReflectionBlob");

		return pBlob;
	}
}