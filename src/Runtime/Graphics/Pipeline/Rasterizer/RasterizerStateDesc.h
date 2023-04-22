#pragma once
#include <Runtime/Graphics/Pipeline/Rasterizer/FaceCullMode.h>
#include <Runtime/Graphics/Pipeline/Rasterizer/MeshShadeMode.h>
#include <Runtime/Graphics/Pipeline/Rasterizer/FrontFaceDirection.h>

namespace Portakal
{
	/// <summary>
	/// Required information to specify a rasterizer state for a pipeline
	/// </summary>
	struct PORTAKAL_API RasterizerStateDesc
	{
		/// <summary>
		/// The back face culling mode
		/// </summary>
		FaceCullMode CullMode;

		/// <summary>
		/// The shading mode
		/// </summary>
		MeshShadeMode ShadeMode;

		/// <summary>
		/// The front face specification
		/// </summary>
		FrontFaceDirection FrontFace;

		/// <summary>
		/// Whether the deph clipping is enabled or not
		/// </summary>
		bool bDepthClipEnabled;

		/// <summary>
		/// Whether the scissor test is enabled or not
		/// </summary>
		bool bScissorTestEnabled;

		int DepthBias;
		float DepthBiasClamp;
		float DepthBiasSlope;
	};
}