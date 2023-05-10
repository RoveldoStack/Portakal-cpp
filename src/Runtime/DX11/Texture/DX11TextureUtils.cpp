#include "DX11TextureUtils.h"

namespace Portakal
{
	UINT DX11TextureUtils::GetTextureUsageFlags(TextureUsage usage)
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
		UINT flags = 0;
		if (usage & TextureUsage::CpuWrite)
		{
			flags |= D3D11_CPU_ACCESS_WRITE;
		}
		if (usage & TextureUsage::CpuRead)
		{
			flags |= D3D11_CPU_ACCESS_READ;
		}

		return flags;
	}
	D3D11_USAGE DX11TextureUtils::GetUsage(const TextureUsage usage)
	{
		D3D11_USAGE usageOut = D3D11_USAGE_DEFAULT;

		if (usage & TextureUsage::CpuWrite && usage & TextureUsage::CpuRead)
			usageOut = D3D11_USAGE_STAGING;
		else if (usage & TextureUsage::CpuWrite)
			usageOut = D3D11_USAGE_DYNAMIC;

		return usageOut;
	}
}