#pragma once
#include <Runtime/Graphics/GraphicsPipelineCreateDesc.h>
#include <d3d11.h>
namespace Portakal
{
	class PORTAKAL_API DX11PipelineUtils
	{
	public:
		DX11PipelineUtils() = delete;
		~DX11PipelineUtils() = delete;

		FORCEINLINE static D3D11_COMPARISON_FUNC GetComparision(const ComparisionMethod method);
		FORCEINLINE static String GetSemanticName(const InputElementSemantic semantic);
		FORCEINLINE static D3D11_CULL_MODE GetCullMode(const FaceCullMode mode);
		FORCEINLINE static D3D11_FILL_MODE GetFillMode(const MeshShadeMode mode);
		FORCEINLINE static D3D11_STENCIL_OP GetStencilOperation(const StencilOperation operation);
		static D3D11_DEPTH_STENCILOP_DESC GetStencilFaceDesc(const StencilFaceDesc& desc);
		FORCEINLINE static D3D11_BLEND GetBlendFactor(const BlendFactor factor);
		FORCEINLINE static D3D11_BLEND_OP GetBlendingOperation(const BlendFunction function);
		static D3D11_RENDER_TARGET_BLEND_DESC GetBlendingAttachmentDesc(const BlendingAttachmentDesc& desc);
		FORCEINLINE static D3D11_PRIMITIVE_TOPOLOGY GetTopology(const MeshTopology topology);

	};
}