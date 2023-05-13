#pragma once
#include <Runtime/Graphics/Pipeline/Pipeline.h>

namespace Portakal
{
	/// <summary>
	/// Represents a whole pipeline configuration.(IA,shaders, resource layouts, rasterizer,blending,depth&stencil and OM states)
	/// </summary>
	class PORTAKAL_API RenderingPath
	{
	public:
		RenderingPath(const GraphicsPipelineCreateDesc& desc,GraphicsDevice* pDevice);
		RenderingPath(const ComputePipelineCreateDesc& desc, GraphicsDevice* pDevice);
		~RenderingPath();

		/// <summary>
		/// Returns the created path pipeline
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Pipeline* GetPipeline() const noexcept { return mPipeline; }

		/// <summary>
		/// Returns a reference to the graphics pipeline configuration desc
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const GraphicsPipelineCreateDesc& GetGraphicsDesc() const noexcept { return mGraphicsDesc; }

		/// <summary>
		/// Returns a reference to the compute pipeline configuration desc
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const ComputePipelineCreateDesc& GetComputeDesc() const noexcept { return mComputeDesc; }
	private:
		Pipeline* mPipeline;
		GraphicsPipelineCreateDesc mGraphicsDesc;
		ComputePipelineCreateDesc mComputeDesc;
	};
}