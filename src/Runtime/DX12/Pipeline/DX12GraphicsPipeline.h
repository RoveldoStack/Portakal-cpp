#pragma once
#include <Runtime/Graphics/Pipeline/Pipeline.h>
#include <Runtime/DX12/Core.h>
#include <d3d12.h>

namespace Portakal
{
	class PORTAKAL_API DX12GraphicsPipeline : public Pipeline
	{
	public:
		DX12GraphicsPipeline(const GraphicsPipelineCreateDesc& desc, DX12Device* pDevice);
		virtual ~DX12GraphicsPipeline() override;

		FORCEINLINE ID3D12PipelineState* GetDXPipelineState() const noexcept { return mPso.Get(); }
		FORCEINLINE ID3D12RootSignature* GetDXRootSignature() const noexcept { return mRootSignature.Get(); }
		FORCEINLINE D3D12_PRIMITIVE_TOPOLOGY GetDXTopology() const noexcept { return mTopology; }
	private:
		DXPTR<ID3D12PipelineState> mPso;
		DXPTR<ID3D12RootSignature> mRootSignature;
		DXPTR<ID3DBlob> mRootSignatureBlob;
		DXPTR<ID3DBlob> mRootSignatureErrorBlob;
		D3D12_PRIMITIVE_TOPOLOGY mTopology;

		// Inherited via Pipeline
		virtual void OnDestroy() override;
	};
}