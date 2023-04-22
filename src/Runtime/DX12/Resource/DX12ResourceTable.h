#pragma once
#include <Runtime/Graphics/Resource/ResourceTable.h>
#include <Runtime/DX12/Core.h>
#include <d3d12.h>

namespace Portakal
{
	class PORTAKAL_API DX12ResourceTable : public ResourceTable
	{
	public:
		DX12ResourceTable(const ResourceTableCreateDesc& desc, DX12Device* pDevice);
		virtual ~DX12ResourceTable() override;

		FORCEINLINE ID3D12DescriptorHeap* GetDXCbvSrvUavHeap() const noexcept { return mCbvSrvUavHeap.Get(); }
		FORCEINLINE ID3D12DescriptorHeap* GetDXSamplerHeap() const noexcept { return mSamplerHeap.Get(); }

	private:
		// Inherited via GraphicsResourceTable
		virtual void OnDestroy() override;
		// Inherited via ResourceTable
		virtual void* GetHandle() const noexcept override;

	private:
		DXPTR<ID3D12DescriptorHeap> mCbvSrvUavHeap;
		DXPTR<ID3D12DescriptorHeap> mSamplerHeap;

	};
}