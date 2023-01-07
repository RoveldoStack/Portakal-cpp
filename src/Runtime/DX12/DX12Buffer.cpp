#include "DX12Buffer.h"
#include <Runtime/DX12/DX12Device.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/DX12/DX12BufferUtils.h>

namespace Portakal
{
	DX12Buffer::DX12Buffer(const GraphicsBufferCreateDesc& desc, DX12Device* pDevice) : GraphicsBuffer(desc)
	{
		_vertexBufferView = {};
		_indexBufferView = {};
		_constantBufferView = {};

		ID3D12Device* pDXDevice = pDevice->GetDXDevice();

		/*
		* Create buffer
		*/
		D3D12_HEAP_PROPERTIES heapProps = {};
		heapProps.Type = D3D12_HEAP_TYPE_CUSTOM;
		heapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
		heapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
		heapProps.VisibleNodeMask = 0;
		heapProps.CreationNodeMask = 0;

		D3D12_RESOURCE_DESC resourceDesc = {};
		resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
		resourceDesc.MipLevels = 1;
		resourceDesc.Alignment = 0;
		resourceDesc.DepthOrArraySize = 1;
		resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resourceDesc.Height = 1;
		resourceDesc.Width = desc.SubItemCount * desc.SubItemSize;
		resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		resourceDesc.SampleDesc.Count = 1;
		resourceDesc.SampleDesc.Quality = 0;

		ASSERT(SUCCEEDED(pDXDevice->CreateCommittedResource(&heapProps,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&_resource))), "DX12Buffer", "Failed to create committed resource");

		switch (desc.Type)
		{
			case Portakal::GraphicsBufferType::VertexBuffer:
			{
				D3D12_VERTEX_BUFFER_VIEW bufferView = {};
				bufferView.BufferLocation = _resource->GetGPUVirtualAddress();
				bufferView.StrideInBytes = desc.SubItemSize;
				bufferView.SizeInBytes = desc.SubItemCount * desc.SubItemCount;

				_vertexBufferView = bufferView;
				break;
			}
			case Portakal::GraphicsBufferType::IndexBuffer:
			{
				D3D12_INDEX_BUFFER_VIEW bufferView = {};
				bufferView.BufferLocation = _resource->GetGPUVirtualAddress();
				bufferView.SizeInBytes = desc.SubItemCount * desc.SubItemSize;
				bufferView.Format = DX12BufferUtils::GetIndexFormat(desc.SubItemSize);

				_indexBufferView = bufferView;
				break;
			}
			case Portakal::GraphicsBufferType::ConstantBuffer:
				break;
			default:
				break;
		}
	}
	DX12Buffer::~DX12Buffer()
	{

	}
}