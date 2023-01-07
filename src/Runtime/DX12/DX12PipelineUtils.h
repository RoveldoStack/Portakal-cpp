#pragma once
#include <Runtime/Graphics/GraphicsPipelineCreateDesc.h>
#include <Runtime/Graphics/ComparisionMethod.h>
#include <d3d12.h>

namespace Portakal
{
	class PORTAKAL_API DX12PipelineUtils
	{
	public:
		DX12PipelineUtils() = delete;
		~DX12PipelineUtils() = delete;

		FORCEINLINE static D3D12_COMPARISON_FUNC GetComparisionMethod(const ComparisionMethod method);

		FORCEINLINE static String GetInputElementSemanticName(const InputElementSemantic semantic);
		FORCEINLINE static D3D12_CULL_MODE GetCullMode(const FaceCullMode mode);
		FORCEINLINE static D3D12_FILL_MODE GetFillMode(const MeshShadeMode mode);

		FORCEINLINE static D3D12_PRIMITIVE_TOPOLOGY_TYPE GetTopologyType(const MeshTopology topology);
		FORCEINLINE static D3D12_PRIMITIVE_TOPOLOGY GetTopology(const MeshTopology topology);

		FORCEINLINE static D3D12_COMPARISON_FUNC GetDepthFunction(const ComparisionMethod method);
		FORCEINLINE static D3D12_COMPARISON_FUNC GetStencilFunction(const ComparisionMethod method);

		FORCEINLINE static D3D12_STENCIL_OP GetStencilOperation(const StencilOperation operation);
		FORCEINLINE static D3D12_DEPTH_STENCILOP_DESC GetStencilFaceDesc(const StencilFaceDesc& desc);

		FORCEINLINE static D3D12_BLEND_OP GetBlendingOperation(const BlendFunction function);
		FORCEINLINE static D3D12_BLEND GetBlendingColorFactor(const BlendFactor factor);
		FORCEINLINE static D3D12_BLEND GetBlendingAlphaFactor(const BlendFactor factor);

		FORCEINLINE static D3D12_RENDER_TARGET_BLEND_DESC GetBlendingAttachmentDesc(const BlendingAttachmentDesc& desc);

		FORCEINLINE static D3D12_SHADER_VISIBILITY GetShaderStageVisibility(const ShaderStage stage);
		FORCEINLINE static D3D12_ROOT_PARAMETER_TYPE GetRootParameterType(const GraphicsResourceType type);
		FORCEINLINE static D3D12_DESCRIPTOR_RANGE_TYPE GetDescriptorRangeType(const GraphicsResourceType type);
	};
}