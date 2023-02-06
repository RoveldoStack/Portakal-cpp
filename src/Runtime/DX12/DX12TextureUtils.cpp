#include "DX12TextureUtils.h"
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	D3D12_RESOURCE_DIMENSION DX12TextureUtils::GetTextureDimension(TextureType type)
	{
		switch (type)
		{
			case Portakal::TextureType::Texture1D:
				return D3D12_RESOURCE_DIMENSION_TEXTURE1D;
			case Portakal::TextureType::Texture2D:
				return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			case Portakal::TextureType::Texture3D:
				return D3D12_RESOURCE_DIMENSION_TEXTURE3D;
			default:
				ASSERT(false, "DX12TextureUtils", "Invalid TextureType!");
				break;
		}
	}
	D3D12_RESOURCE_FLAGS DX12TextureUtils::GetTextureResourceFlags(const TextureUsage usage)
	{
		D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE;

		if (!(usage & TextureUsage::ReadOnly) && !(usage & TextureUsage::RenderTarget) && !(usage & TextureUsage::DepthStencil))
			flags |= D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;
		if (usage & TextureUsage::RenderTarget)
			flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
		if (usage & TextureUsage::DepthStencil)
			flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

		return flags;
	}
}