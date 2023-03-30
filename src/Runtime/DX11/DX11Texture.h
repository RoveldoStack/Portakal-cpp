#pragma once
#include <Runtime/Graphics/Texture.h>
#include <Runtime/DX11/Core.h>
#include <d3d11.h>

namespace Portakal
{
	class PORTAKAL_API DX11Texture : public Texture
	{
	public:
		/// <summary>
		/// Used for normal texture creation
		/// </summary>
		/// <param name="desc"></param>
		/// <param name="pDevice"></param>
		DX11Texture(const TextureCreateDesc& desc,DX11Device* pDevice);

		/// <summary>
		/// Used for swapchain texture creation
		/// </summary>
		/// <param name="desc"></param>
		/// <param name="texture"></param>
		/// <param name="pDevice"></param>
		DX11Texture(const TextureCreateDesc& desc,const DXPTR<ID3D11Resource>& texture, DX11Device* pDevice);

		FORCEINLINE ID3D11Resource* GetDXTexture() const noexcept { return mTexture.Get(); }
	private:
		virtual void OnDestroy() override;
	private:
		ComPtr<ID3D11Resource> mTexture;
	};
}