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
		for (unsigned int i = 0; i < desc.Resources.GetCursor(); i++)
		{
			const GraphicsDeviceObject* pObject = desc.Resources[i];

			switch (pObject->GetDeviceObjectType())
			{
				case Portakal::GraphicsDeviceObjectType::Buffer:
				{
					DX11Buffer* pBuffer = (DX11Buffer*)pObject;

					ASSERT(pBuffer->GetBufferType() == GraphicsBufferType::ConstantBuffer, "DX11ResourceTable", "Invalid buffer resource type!");

					mBuffers.Add(pBuffer->GetDXBuffer());
					break;
				}
				case Portakal::GraphicsDeviceObjectType::Texture:
				{
					DXPTR<ID3D11ShaderResourceView> srv;
					Texture* pTexture = (Texture*)pObject;

					D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
					srvDesc.Format = DXGIUtils::GetTextureFormat(pTexture->GetTextureFormat());
					srvDesc.Texture2D.MipLevels = 1;
					srvDesc.Texture2D.MostDetailedMip = 0;
					srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

					ASSERT(SUCCEEDED(pDevice->GetDXDevice()->CreateShaderResourceView(((DX11Texture*)pTexture)->GetDXTexture(), &srvDesc, srv.GetAddressOf())), "DX11ResourceTable", "Failed to create texture resource view");

					mSrvs.Add(srv);
					mSrvsRaw.Add(srv.Get());
					break;
				}
				case Portakal::GraphicsDeviceObjectType::Sampler:
				{
					DX11Sampler* pSampler = (DX11Sampler*)pObject;

					mSamplers.Add(pSampler->GetDXSampler());
					break;
				}
				default:
					ASSERT(false, "DX12ResourceTable", "Invalid resource!");
					break;
				}
		}

    }
    DX11ResourceTable::~DX11ResourceTable()
    {
    }
    void DX11ResourceTable::OnDestroy()
    {
    }
    void* DX11ResourceTable::GetHandle() const noexcept
    {
        return mSrvs[0].Get();
    }
}