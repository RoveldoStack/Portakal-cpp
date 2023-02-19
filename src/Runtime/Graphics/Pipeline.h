#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/GraphicsPipelineCreateDesc.h>
#include <Runtime/Graphics/PipelineBindPoint.h>

namespace Portakal
{
	/// <summary>
	/// Represents the pipeline object for the graphics/compute pipeline
	/// </summary>
	class PORTAKAL_API Pipeline : public GraphicsDeviceObject
	{
	public:
		/// <summary>
		/// Returns the blending state
		/// </summary>
		/// <returns></returns>
		FORCEINLINE BlendingStateDesc GetBlendingState() const noexcept { return mCreateDesc.BlendingState; }

		/// <summary>
		/// Returns the depth stencil state
		/// </summary>
		/// <returns></returns>
		FORCEINLINE DepthStencilStateDesc GetDepthStencilState() const noexcept { return mCreateDesc.DepthStencilState; }

		/// <summary>
		/// Returns the rasterizer state
		/// </summary>
		/// <returns></returns>
		FORCEINLINE RasterizerStateDesc GetRasterizerState() const noexcept { return mCreateDesc.RasterizerState; }

		/// <summary>
		/// Returns the mesh topology
		/// </summary>
		/// <returns></returns>
		FORCEINLINE MeshTopology GetMeshTopology() const noexcept { return mCreateDesc.MeshTopology; }

		/// <summary>
		/// Returns the shader set attached to the pipeline
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<Shader*> GetShaders() const noexcept { return mCreateDesc.Shaders; }

		/// <summary>
		/// Returns the input layout
		/// </summary>
		/// <returns></returns>
		FORCEINLINE InputLayoutDesc GetInputLayout() const noexcept { return mCreateDesc.InputLayout; }

		/// <summary>
		/// Returns the resource state of the pipeline
		/// </summary>
		/// <returns></returns>
		FORCEINLINE ResourceStateDesc GetResourceState() const noexcept { return mCreateDesc.ResourceState; }

		/// <summary>
		/// Returns the binding point of the pipeline (Graphics/Compute)
		/// </summary>
		/// <returns></returns>
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