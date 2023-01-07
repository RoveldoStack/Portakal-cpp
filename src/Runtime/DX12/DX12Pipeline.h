#pragma once
#include <Runtime/Graphics/Pipeline.h>
#include <Runtime/DX12/Core.h>
#include <d3d12.h>

namespace Portakal
{
	class PORTAKAL_API DX12Pipeline : public Pipeline
	{
	public:
		DX12Pipeline(const GraphicsPipelineCreateDesc& desc, DX12Device* pDevice);
		virtual ~DX12Pipeline() override;

		FORCEINLINE ID3D12PipelineState* GetDXPipelineState() const noexcept { return _pipelineState.Get(); }
		FORCEINLINE ID3D12RootSignature* GetDXRootSignature() const noexcept { return _rootSignature.Get(); }
		FORCEINLINE D3D12_PRIMITIVE_TOPOLOGY GetDXTopology() const noexcept { return _topology; }
	private:
		DXPTR<ID3D12PipelineState> _pipelineState;
		DXPTR<ID3D12RootSignature> _rootSignature;
		DXPTR<ID3DBlob> _rootSignatureBlob;
		DXPTR<ID3DBlob> _rootSignatureErrorBlob;
		D3D12_PRIMITIVE_TOPOLOGY _topology;
	};
}