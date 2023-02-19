#pragma once
#include <Runtime/Graphics/StencilFaceDesc.h>

namespace Portakal
{
	/// <summary>
	/// Required information to create the depth stencil state for a pipeline
	/// </summary>
	struct PORTAKAL_API DepthStencilStateDesc
	{
		/// <summary>
		/// Whether the depth testing is enabled
		/// </summary>
		bool bDepthTestEnabled;

		/// <summary>
		/// Whether the depth writing is enabled
		/// </summary>
		bool bDepthWriteEnabled;

		/// <summary>
		/// The depth comparision method
		/// </summary>
		ComparisionMethod DepthComparision;

		/// <summary>
		/// Whether the stencil test is enabled
		/// </summary>
		bool bStencilTestEnabled;

		/// <summary>
		/// Stencil front face behaviour
		/// </summary>
		StencilFaceDesc StencilFrontFace;

		/// <summary>
		/// Stencil back face behaviour
		/// </summary>
		StencilFaceDesc StencilBackFace;

		/// <summary>
		/// Stencil read mask value
		/// </summary>
		unsigned char StencilReadMask;

		/// <summary>
		/// Stencil write mask value
		/// </summary>
		unsigned char StencilWriteMask;

		/// <summary>
		/// Stencil reference value
		/// </summary>
		unsigned char StencilReference;
	};
}