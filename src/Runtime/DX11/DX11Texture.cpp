#include "DX11Texture.h"
#include <Runtime/DX11/DX11Device.h>
#include <Runtime/DXGI/DXGIUtils.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/DX11/DX11TextureUtils.h>
namespace Portakal
{
	ComPtr<ID3D11Resource> CreateTexture1D(const TextureCreateDesc& desc, DX11Device* pDevice)
	{
		ComPtr<ID3D11Texture1D> texture;

		D3D11_TEXTURE1D_DESC textureDesc = {};
		textureDesc.Width = desc.Width;
		textureDesc.ArraySize = desc.ArrayLevels;
		textureDesc.MipLevels = desc.MipLevels;
		textureDesc.MiscFlags = 0;
		textureDesc.BindFlags = DX11TextureUtils::GetTextureUsageFlags(desc.Usage);
		textureDesc.CPUAccessFlags = DX11TextureUtils::GetCpuFlags(desc.Usage);
		textureDesc.Format = DXGIUtils::GetTextureFormat(desc.Format);
		textureDesc.Usage = DX11TextureUtils::GetUsage(desc.Usage);

		pDevice->GetDXDevice()->CreateTexture1D(&textureDesc, nullptr, texture.GetAddressOf());

		ComPtr<ID3D11Resource> resource;

		ASSERT(SUCCEEDED(texture.As<ID3D11Resource>(&resource)), "DX11Texture", "Failed to convert texture1d to resource");

		return resource;
	}
	ComPtr<ID3D11Resource> CreateTexture2D(const TextureCreateDesc& desc,DX11Device* pDevice)
	{
		ComPtr<ID3D11Texture2D> texture;

		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = desc.Width;
		textureDesc.Height = desc.Height;
		textureDesc.ArraySize = desc.ArrayLevels;
		textureDesc.MipLevels = desc.MipLevels;
		textureDesc.SampleDesc.Count = desc.SampleCount;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.MiscFlags = 0;
		textureDesc.BindFlags = DX11TextureUtils::GetTextureUsageFlags(desc.Usage);
		textureDesc.CPUAccessFlags = DX11TextureUtils::GetCpuFlags(desc.Usage);
		textureDesc.Format = DXGIUtils::GetTextureFormat(desc.Format);
		textureDesc.Usage = DX11TextureUtils::GetUsage(desc.Usage);

		
		ASSERT(SUCCEEDED(pDevice->GetDXDevice()->CreateTexture2D(&textureDesc, nullptr, texture.GetAddressOf())), "DX11Texture", "Failed to convert texture2d to resource");
		ComPtr<ID3D11Resource> resource;
		
		ASSERT(SUCCEEDED(texture.As<ID3D11Resource>(&resource)), "DX11Texture", "Failed to convert texture2d to resource");

		return resource;
	}
	ComPtr<ID3D11Resource> CreateTexture3D(const TextureCreateDesc& desc, DX11Device* pDevice)
	{
		ComPtr<ID3D11Texture3D> texture;

		D3D11_TEXTURE3D_DESC textureDesc = {};
		textureDesc.Width = desc.Width;
		textureDesc.Height = desc.Height;
		textureDesc.Depth = desc.Depth;
		textureDesc.MipLevels = desc.MipLevels;
		textureDesc.MiscFlags = 0;
		textureDesc.BindFlags = DX11TextureUtils::GetTextureUsageFlags(desc.Usage);
		textureDesc.CPUAccessFlags = DX11TextureUtils::GetCpuFlags(desc.Usage);
		textureDesc.Format = DXGIUtils::GetTextureFormat(desc.Format);
		textureDesc.Usage = DX11TextureUtils::GetUsage(desc.Usage);

		pDevice->GetDXDevice()->CreateTexture3D(&textureDesc, nullptr, texture.GetAddressOf());

		ComPtr<ID3D11Resource> resource;

		ASSERT(SUCCEEDED(texture.As<ID3D11Resource>(&resource)), "DX11Texture", "Failed to convert texture3d to resource");

		return resource;
	}
	DX11Texture::DX11Texture(const TextureCreateDesc& desc,DX11Device* pDevice) : Texture(desc)
	{

		switch (desc.Type)
		{
			case Portakal::TextureType::Texture1D:
			{
				mTexture = CreateTexture1D(desc, pDevice);
				break;
			}
			case Portakal::TextureType::Texture2D:
			{
				mTexture = CreateTexture2D(desc,pDevice);
				break;
			}
			case Portakal::TextureType::Texture3D:
			{
				mTexture = CreateTexture3D(desc, pDevice);
				break;
			}
			default:
				ASSERT(false, "DX11Texture", "Invalid texture type");
				break;
		}
	}
	DX11Texture::DX11Texture(const TextureCreateDesc& desc, const DXPTR<ID3D11Resource>& texture, DX11Device* pDevice) : Texture(desc)
	{
		mTexture = texture;
	}
	void DX11Texture::OnDestroy()
	{
		mTexture.Reset();
	}
}