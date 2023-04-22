#pragma once
#include <Runtime/Graphics/Texture/Texture.h>
#include <Runtime/DX12/Core.h>
#include <Runtime/DX12/DX12Resource.h>
#include <d3d12.h>

namespace Portakal
{
	class PORTAKAL_API DX12Texture : public Texture, public DX12Resource
	{
	public:
		DX12Texture(const TextureCreateDesc& desc, DX12Device* pDevice);
		DX12Texture(const DXPTR<ID3D12Resource>& swapchainRTVResource,const TextureCreateDesc& desc);
		~DX12Texture() = default;

		FORCEINLINE ID3D12Resource* GetDXTexture() const noexcept { return mResource.Get(); }
	private:
		DXPTR<ID3D12Resource> mResource;

		// Inherited via Texture
		virtual void OnDestroy() override;
	};
}