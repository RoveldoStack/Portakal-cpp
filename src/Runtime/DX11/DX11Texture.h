#pragma once
#include <Runtime/Graphics/Texture.h>
#include <Runtime/DX11/Core.h>
#include <d3d11.h>

namespace Portakal
{
	class PORTAKAL_API DX11Texture : public Texture
	{
	public:
		DX11Texture(const TextureCreateDesc& desc,DX11Device* pDevice);
		virtual ~DX11Texture() override;

		FORCEINLINE ID3D11Resource* GetDXTexture() const noexcept { return mTexture.Get(); }
	private:
		virtual void OnDestroy() override;
	private:
		ComPtr<ID3D11Resource> mTexture;
	};
}