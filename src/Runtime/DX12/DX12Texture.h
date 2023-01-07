#pragma once
#include <Runtime/Graphics/Texture.h>
#include <Runtime/DX12/Core.h>
#include <d3d12.h>

namespace Portakal
{
	class PORTAKAL_API DX12Texture : public Texture
	{
	public:
		DX12Texture(const TextureCreateDesc& desc, DX12Device* pDevice);
		DX12Texture(const DXPTR<ID3D12Resource>& swapchainRTVResource,const TextureCreateDesc& desc);
		virtual ~DX12Texture() override;

		FORCEINLINE ID3D12Resource* GetDXTexture() const noexcept { return _resource.Get(); }
	private:
		DXPTR<ID3D12Resource> _resource;
	};
}