#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/GraphicsPipelineCreateDesc.h>

namespace Portakal
{
	class PORTAKAL_API Pipeline : public GraphicsDeviceObject
	{
	public:
		FORCEINLINE BlendingStateDesc GetBlendingState() const noexcept { return _createDesc.BlendingState; }
		FORCEINLINE DepthStencilStateDesc GetDepthStencilState() const noexcept { return _createDesc.DepthStencilState; }
		FORCEINLINE RasterizerStateDesc GetRasterizerState() const noexcept { return _createDesc.RasterizerState; }
		FORCEINLINE MeshTopology GetMeshTopology() const noexcept { return _createDesc.MeshTopology; }
		FORCEINLINE Array<Shader*> GetShaders() const noexcept { return _createDesc.Shaders; }
		FORCEINLINE InputLayoutDesc GetInputLayout() const noexcept { return _createDesc.InputLayout; }
		FORCEINLINE ResourceStateDesc GetResourceState() const noexcept { return _createDesc.ResourceState; }

		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override { return GraphicsDeviceObjectType::Pipeline; }
	protected:
		Pipeline(const GraphicsPipelineCreateDesc& desc) : _createDesc(desc) {}
		virtual ~Pipeline() {}

	
	private:
		const GraphicsPipelineCreateDesc _createDesc;
	};
}