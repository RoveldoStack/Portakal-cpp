#include "DX12ResourceTable.h"
#include <Runtime/DX12/DX12DeviceObjects.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/DX12/DX12Device.h>
#include "DX12ResourceUtils.h"
#include <Runtime/DXGI/DXGIUtils.h>
#include <Runtime/DX12/Sampler/DX12SamplerUtils.h>
#include <Runtime/DX12/Pipeline/DX12PipelineUtils.h>


namespace Portakal
{
	DX12ResourceTable::DX12ResourceTable(const ResourceTableCreateDesc& desc, DX12Device* pDevice) : ResourceTable(desc)
	{
		Array<DX12Sampler*> samplers;
		Array<const GraphicsDeviceObject*> cbvsrvs;

		/*
		* Collect resources
		*/
		for (unsigned int i = 0; i < desc.Resources.GetCursor(); i++)
		{
			const GraphicsDeviceObject* pObject = (const GraphicsDeviceObject*)desc.Resources[i];

			switch (pObject->GetDeviceObjectType())
			{
				case Portakal::GraphicsDeviceObjectType::Buffer:
					cbvsrvs.Add(pObject);
					break;
				case Portakal::GraphicsDeviceObjectType::Texture:
					cbvsrvs.Add(pObject);
					break;
				case Portakal::GraphicsDeviceObjectType::Sampler:
					samplers.Add((DX12Sampler*)pObject);
					break;
				default:
					ASSERT(false, "DX12ResourceTable", "Invalid resource!");
					break;
			}
		}

		/*
		* Create heaps
		*/
		if (cbvsrvs.GetCursor() > 0)
		{
			D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = {};
			descriptorHeapDesc.NumDescriptors = cbvsrvs.GetCursor();
			descriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
			descriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

			pDevice->GetDXDevice()->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&mCbvSrvUavHeap));
		}
		if (samplers.GetCursor() > 0)
		{
			D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = {};
			descriptorHeapDesc.NumDescriptors = samplers.GetCursor();
			descriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
			descriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;

			pDevice->GetDXDevice()->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&mSamplerHeap));
		}

		/*
		* Create resource views for cbv_srv
		*/
		{
			if (cbvsrvs.GetCursor() > 0)
			{
				D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = mCbvSrvUavHeap->GetCPUDescriptorHandleForHeapStart();
				const unsigned int cpuHandleIncrementSize = pDevice->GetDXDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

				for (unsigned int i = 0; i < cbvsrvs.GetCursor(); i++)
				{
					const GraphicsDeviceObject* pObject = cbvsrvs[i];

					switch (pObject->GetDeviceObjectType())
					{
					case Portakal::GraphicsDeviceObjectType::Buffer:
					{
						const DX12Buffer* pBuffer = (const DX12Buffer*)pObject;

						D3D12_CONSTANT_BUFFER_VIEW_DESC bufferViewDesc = {};
						bufferViewDesc.SizeInBytes = pBuffer->GetSubItemSize();
						bufferViewDesc.BufferLocation = pBuffer->GetDXResource()->GetGPUVirtualAddress();

						pDevice->GetDXDevice()->CreateConstantBufferView(&bufferViewDesc, cpuHandle);
						break;
					}
					case Portakal::GraphicsDeviceObjectType::Texture:
					{
						const DX12Texture* pTexture = (const DX12Texture*)pObject;

						D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
						srvDesc.ViewDimension = DX12ResourceUtils::GetTextureSRVDimension(pTexture->GetTextureType());
						srvDesc.Format = DXGIUtils::GetTextureFormat(pTexture->GetTextureFormat());
						srvDesc.Texture2D.MipLevels = 1;
						srvDesc.Texture2D.MostDetailedMip = 0;
						srvDesc.Texture2D.PlaneSlice = 0;
						srvDesc.Texture2D.ResourceMinLODClamp = 0;
						srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

						pDevice->GetDXDevice()->CreateShaderResourceView(pTexture->GetDXTexture(), &srvDesc, cpuHandle);
						break;
					}
					}

					cpuHandle.ptr += cpuHandleIncrementSize;
				}
			}
		}

		/*
		* Create samplers
		*/
		{
			if (samplers.GetCursor() > 0)
			{
				D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = mSamplerHeap->GetCPUDescriptorHandleForHeapStart();
				const unsigned int cpuHandleIncrementSize = pDevice->GetDXDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);
				for (unsigned int i = 0; i < samplers.GetCursor(); i++)
				{
					const DX12Sampler* pSampler = (const DX12Sampler*)samplers[i];

					D3D12_SAMPLER_DESC samplerDesc = {};
					samplerDesc.AddressU = DX12SamplerUtils::GetWrapMode(pSampler->GetAddressU());
					samplerDesc.AddressV = DX12SamplerUtils::GetWrapMode(pSampler->GetAddressV());
					samplerDesc.AddressW = DX12SamplerUtils::GetWrapMode(pSampler->GetAddressW());
					samplerDesc.BorderColor[0] = 0;
					samplerDesc.BorderColor[1] = 0;
					samplerDesc.BorderColor[2] = 0;
					samplerDesc.BorderColor[3] = 0;
					samplerDesc.ComparisonFunc = DX12PipelineUtils::GetComparisionMethod(pSampler->GetComparisionMethod());
					samplerDesc.Filter = DX12SamplerUtils::GetFilter(pSampler->GetFiltering());
					samplerDesc.MaxAnisotropy = pSampler->GetMaxAnisotropy();
					samplerDesc.MaxLOD = pSampler->GetMaxLod();
					samplerDesc.MinLOD = pSampler->GetMinLod();
					samplerDesc.MipLODBias = pSampler->GetLodBias();

					pDevice->GetDXDevice()->CreateSampler(&samplerDesc, cpuHandle);

					cpuHandle.ptr += cpuHandleIncrementSize;
				}
			}
		}

	}
	DX12ResourceTable::~DX12ResourceTable()
	{
		mCbvSrvUavHeap.Reset();
		mSamplerHeap.Reset();
	}
	void DX12ResourceTable::OnDestroy()
	{
	}
	void* DX12ResourceTable::GetHandle() const noexcept
	{
		return mCbvSrvUavHeap.Get();
	}
}