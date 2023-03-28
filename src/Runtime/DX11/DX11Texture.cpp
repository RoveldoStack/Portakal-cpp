#include "DX11Texture.h"
#include <Runtime/DX11/DX11Device.h>
#include <Runtime/DXGI/DXGIUtils.h>
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	ComPtr<ID3D11Resource> CreateTexture2D(const TextureCreateDesc& desc,DX11Device* pDevice)
	{
		ComPtr<ID3D11Texture2D> texture;

		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = desc.Width;
		textureDesc.Height = desc.Height;
		textureDesc.ArraySize = desc.ArrayLevels;
		textureDesc.MipLevels = desc.MipLevels;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.MiscFlags = 0;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		textureDesc.Format = DXGIUtils::GetTextureFormat(desc.Format);
		textureDesc.Usage = D3D11_USAGE_DYNAMIC;

		pDevice->GetDXDevice()->CreateTexture2D(&textureDesc, nullptr, texture.GetAddressOf());

		ComPtr<ID3D11Resource> resource;
		
		ASSERT(SUCCEEDED(texture.As<ID3D11Resource>(&resource)), "DX11Texture", "Failed to convert texture2d to resource");

		return resource;
	}
	DX11Texture::DX11Texture(const TextureCreateDesc& desc,DX11Device* pDevice) : Texture(desc)
	{

		switch (desc.Type)
		{
			case Portakal::TextureType::Texture1D:
				break;
			case Portakal::TextureType::Texture2D:
			{
				mTexture = CreateTexture2D(desc,pDevice);
				break;
			}
			case Portakal::TextureType::Texture3D:
				break;
			default:
				break;
		}
	}
	DX11Texture::~DX11Texture()
	{

	}
	void DX11Texture::OnDestroy()
	{
	}
}