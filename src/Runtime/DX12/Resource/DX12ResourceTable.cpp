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
		/*
		* Collect buffers and textures
		*/
		Array<GraphicsDeviceObject*> cbvSrvs;
		for (unsigned int i = 0; i < desc.Buffers.GetCursor(); i++)
			cbvSrvs.Add(desc.Buffers[i]);
		for (unsigned int i = 0; i < desc.Textures.GetCursor(); i++)
			cbvSrvs.Add(desc.Textures[i]);

		/*
		* Create heaps
		*/
		if (cbvSrvs.GetCursor() > 0)
		{
			D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = {};
			descriptorHeapDesc.NumDescriptors = desc.Textures.GetCursor() + desc.Buffers.GetCursor();
			descriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
			descriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

			pDevice->GetDXDevice()->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&mCbvSrvUavHeap));

			D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = mCbvSrvUavHeap->GetCPUDescriptorHandleForHeapStart();
			const unsigned int cpuHandleIncrementSize = pDevice->GetDXDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

			for (unsigned int i = 0; i < cbvSrvs.GetCursor(); i++)
			{
				const GraphicsDeviceObject* pObject = cbvSrvs[i];

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

		/*
		* Create samplers
		*/
		if (desc.Samplers.GetCursor() > 0)
		{
			D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = {};
			descriptorHeapDesc.NumDescriptors = desc.Samplers.GetCursor();
			descriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
			descriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;

			pDevice->GetDXDevice()->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&mSamplerHeap));

			D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = mSamplerHeap->GetCPUDescriptorHandleForHeapStart();
			const unsigned int cpuHandleIncrementSize = pDevice->GetDXDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);
			for (unsigned int i = 0; i < desc.Samplers.GetCursor(); i++)
			{
				const DX12Sampler* pSampler = (const DX12Sampler*)desc.Samplers[i];

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
	DX12ResourceTable::~DX12ResourceTable()
	{
		
	}
	void DX12ResourceTable::OnDestroy()
	{
		mCbvSrvUavHeap.Reset();
		mSamplerHeap.Reset();
	}
}