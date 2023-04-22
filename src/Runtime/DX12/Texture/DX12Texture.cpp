#include "DX12Texture.h"
#include <Runtime/DX12/DX12Device.h>
#include <Runtime/DX12/Texture/DX12TextureUtils.h>
#include <Runtime/DXGI/DXGIUtils.h>
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	DX12Texture::DX12Texture(const TextureCreateDesc& desc, DX12Device* pDevice) : Texture(desc)
	{
		ID3D12Device* pDXDevice = pDevice->GetDXDevice();

		/*
		* Create texture heap properties
		*/
		D3D12_HEAP_PROPERTIES heapProps = {};
		heapProps.Type = D3D12_HEAP_TYPE_DEFAULT;
		heapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		heapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProps.VisibleNodeMask = 0;
		heapProps.CreationNodeMask = 0;

		/*
		* Create texture resource
		*/
		D3D12_RESOURCE_DESC resourceDesc = {};
		resourceDesc.Dimension = DX12TextureUtils::GetTextureDimension(desc.Type);
		resourceDesc.Format = DXGIUtils::GetTextureFormat(desc.Format);
		resourceDesc.MipLevels = 1;
		resourceDesc.Alignment = 0;
		resourceDesc.DepthOrArraySize = desc.Depth == 0 ? 1 : desc.Depth;
		resourceDesc.Flags = DX12TextureUtils::GetTextureResourceFlags(desc.Usage);
		resourceDesc.Width = desc.Width;
		resourceDesc.Height = desc.Height;
		resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		resourceDesc.SampleDesc.Count = 1;
		resourceDesc.SampleDesc.Quality = 0;

		D3D12_CLEAR_VALUE clearValue = {};
		clearValue.Color[0] = 0.0f;
		clearValue.Color[1] = 0.0f;
		clearValue.Color[2] = 0.0f;
		clearValue.Color[3] = 0.0f;
		clearValue.DepthStencil.Depth = 0;
		clearValue.DepthStencil.Stencil = 0;
		clearValue.Format = resourceDesc.Format;

		ASSERT(SUCCEEDED(pDXDevice->CreateCommittedResource(&heapProps,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_COPY_DEST,
			desc.Usage & TextureUsage::RenderTarget || desc.Usage & TextureUsage::DepthStencil ? &clearValue : nullptr,
			IID_PPV_ARGS(&mResource))), "DX12Texture", "Failed to create the texture");


		MutateDXResourceState(D3D12_RESOURCE_STATE_COPY_DEST);
	}
	DX12Texture::DX12Texture(const DXPTR<ID3D12Resource>& swapchainRTVResource, const TextureCreateDesc& desc) : Texture(desc)
	{
		mResource = swapchainRTVResource;
	}
	void DX12Texture::OnDestroy()
	{
		mResource.Reset();
	}

}