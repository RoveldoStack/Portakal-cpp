#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/GraphicsPipelineCreateDesc.h>
#include <Runtime/Graphics/PipelineBindPoint.h>

namespace Portakal
{
	class PORTAKAL_API Pipeline : public GraphicsDeviceObject
	{
	public:
		FORCEINLINE BlendingStateDesc GetBlendingState() const noexcept { return mCreateDesc.BlendingState; }
		FORCEINLINE DepthStencilStateDesc GetDepthStencilState() const noexcept { return mCreateDesc.DepthStencilState; }
		FORCEINLINE RasterizerStateDesc GetRasterizerState() const noexcept { return mCreateDesc.RasterizerState; }
		FORCEINLINE MeshTopology GetMeshTopology() const noexcept { return mCreateDesc.MeshTopology; }
		FORCEINLINE Array<Shader*> GetShaders() const noexcept { return mCreateDesc.Shaders; }
		FORCEINLINE InputLayoutDesc GetInputLayout() const noexcept { return mCreateDesc.InputLayout; }
		FORCEINLINE ResourceStateDesc GetResourceState() const noexcept { return mCreateDesc.ResourceState; }
		FORCEINLINE PipelineBindPoint GetBindPoint() const noexcept { return mBindPoint; }
		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override { return GraphicsDeviceObjectType::Pipeline; }
	protected:
		Pipeline(const GraphicsPipelineCreateDesc& desc) : mCreateDesc(desc),mBindPoint(PipelineBindPoint::Graphics){}
		virtual ~Pipeline() {}

	
	private:
		const GraphicsPipelineCreateDesc mCreateDesc;
		const PipelineBindPoint mBindPoint;
	};
}