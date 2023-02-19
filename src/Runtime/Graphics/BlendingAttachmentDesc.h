#pragma once
#include <Runtime/Graphics/BlendFactor.h>
#include <Runtime/Graphics/BlendFunction.h>
#include <Runtime/Graphics/LogicOperation.h>

namespace Portakal
{
	/// <summary>
	/// Represents a blending configuration for single color target
	/// </summary>
	struct PORTAKAL_API BlendingAttachmentDesc
	{
		/// <summary>
		/// Whether the independent blending is enabled or not
		/// </summary>
		bool bEnabled;

		/// <summary>
		/// Whether the logical operations will be executed or not
		/// </summary>
		bool bEnableLogicOp;

		/// <summary>
		/// The source color blending coef
		/// </summary>
		BlendFactor SourceColorFactor;

		/// <summary>
		/// The destination color blending coef
		/// </summary>
		BlendFactor DestinationColorFactor;

		/// <summary>
		/// The color function
		/// </summary>
		BlendFunction ColorFunction;

		/// <summary>
		/// The source alpha blending coef
		/// </summary>
		BlendFactor SourceAlphaFactor;

		/// <summary>
		/// The destination alpha blending coef
		/// </summary>
		BlendFactor DestinationAlphaFactor;

		/// <summary>
		/// The alpha function
		/// </summary>
		BlendFunction AlphaFunction;

		/// <summary>
		/// The logical operation
		/// </summary>
		LogicOperation LogicOp;

		/// <summary>
		/// Blending write mask
		/// </summary>
		unsigned char WriteMask;
	};
}