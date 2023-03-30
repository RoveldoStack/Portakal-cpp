#include "DX11TextureUtils.h"

namespace Portakal
{
	UINT DX11TextureUtils::GetTextureUsageFlags( TextureUsage usage)
	{
		UINT flags = 0;
		if (usage & TextureUsage::Sampled)
		{
			flags |= D3D11_BIND_SHADER_RESOURCE;
		}
		if (usage & TextureUsage::RenderTarget)
		{
			flags |= D3D11_BIND_RENDER_TARGET;
		}
		else if (usage & TextureUsage::DepthStencil)
		{
			flags |= D3D11_BIND_DEPTH_STENCIL;
		}

		return flags;
	}
	UINT DX11TextureUtils::GetCpuFlags(TextureUsage usage)
	{
		switch (usage)
		{
			case Portakal::TextureUsage::Sampled:
				return D3D11_CPU_ACCESS_WRITE;
			case Portakal::TextureUsage::Storage:
				return D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
			case Portakal::TextureUsage::RenderTarget:
				return 0;
			case Portakal::TextureUsage::DepthStencil:
				return 0;
			case Portakal::TextureUsage::Cubemap:
				return 0;
			case Portakal::TextureUsage::Staging:
				return D3D11_CPU_ACCESS_WRITE;
			default:
				return 0;
				break;
		}

	}
	D3D11_USAGE DX11TextureUtils::GetUsage(const TextureUsage usage)
	{
		switch (usage)
		{
			case Portakal::TextureUsage::Sampled:
				return D3D11_USAGE_DYNAMIC;
			case Portakal::TextureUsage::Storage:
				return D3D11_USAGE_DYNAMIC;
			case Portakal::TextureUsage::RenderTarget:
				return D3D11_USAGE_DEFAULT;
			case Portakal::TextureUsage::DepthStencil:
				return D3D11_USAGE_DEFAULT;
			case Portakal::TextureUsage::Cubemap:
				return D3D11_USAGE_DEFAULT;
			case Portakal::TextureUsage::Staging:
				return D3D11_USAGE_DEFAULT;
			default:
				return D3D11_USAGE_DEFAULT;
				break;
		}
	}
}