#include "DX11ResourceTable.h"
#include <Runtime/DXGI/DXGIUtils.h>
#include <Runtime/DX11/DX11DeviceObjects.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/DX11/DX11Device.h>
#include <Runtime/DX11/Sampler/DX11Sampler.h>

namespace Portakal
{
    DX11ResourceTable::DX11ResourceTable(const ResourceTableCreateDesc& desc, DX11Device* pDevice) : ResourceTable(desc)
    {
		/*
		* Collect buffers
		*/
		for (unsigned int i = 0; i < desc.Buffers.GetCursor(); i++)
		{
			const GraphicsDeviceObject* pObject = (const GraphicsDeviceObject*)desc.Buffers[i];

			DX11Buffer* pBuffer = (DX11Buffer*)pObject;

			ASSERT(pBuffer->GetBufferType() == GraphicsBufferType::ConstantBuffer, "DX11ResourceTable", "Invalid buffer resource type!");

			mBuffers.Add(pBuffer->GetDXBuffer());
		}

		/*
		* Collect textures
		*/
		for (unsigned int i = 0; i < desc.Textures.GetCursor(); i++)
		{
			const GraphicsDeviceObject* pObject = (const GraphicsDeviceObject*)desc.Textures[i];

			ID3D11ShaderResourceView* pSrv = nullptr;
			Texture* pTexture = (Texture*)pObject;

			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
			srvDesc.Format = DXGIUtils::GetTextureFormat(pTexture->GetTextureFormat());
			srvDesc.Texture2D.MipLevels = 1;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

			ASSERT(SUCCEEDED(pDevice->GetDXDevice()->CreateShaderResourceView(((DX11Texture*)pTexture)->GetDXTexture(), &srvDesc, &pSrv)), "DX11ResourceTable", "Failed to create texture resource view");

			mResourceViews.Add(pSrv);
		}

		/*
		* Collect samplers
		*/
		for (unsigned int i = 0; i < desc.Samplers.GetCursor(); i++)
		{
			const GraphicsDeviceObject* pObject = (const GraphicsDeviceObject*)desc.Samplers[i];
			DX11Sampler* pSampler = (DX11Sampler*)pObject;

			mSamplers.Add(pSampler->GetDXSampler());
			break;
		}

    }
    DX11ResourceTable::~DX11ResourceTable()
    {

    }
	
    void DX11ResourceTable::OnDestroy()
    {
		/*
		* Delete resource views
		*/
		for (unsigned int i = 0; i < mResourceViews.GetCursor(); i++)
			mResourceViews[i]->Release();

		/*
		* Clear arrays
		*/
		mBuffers.Clear();
		mSamplers.Clear();
		mResourceViews.Clear();

    }
    void* DX11ResourceTable::GetHandle() const noexcept
    {
		return nullptr;
    }
}