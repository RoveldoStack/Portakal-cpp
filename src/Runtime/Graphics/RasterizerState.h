#pragma once
#include <Runtime/Graphics/FaceCullMode.h>
#include <Runtime/Graphics/MeshShadeMode.h>
#include <Runtime/Graphics/FrontFaceDirection.h>

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
	};
}