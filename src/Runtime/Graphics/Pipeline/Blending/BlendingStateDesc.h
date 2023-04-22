#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/Pipeline/Blending/BlendingAttachmentDesc.h>

namespace Portakal
{
	/// <summary>
	/// Represents the whole blending configuration of a pipeline
	/// </summary>
	struct PORTAKAL_API BlendingStateDesc
	{
		/// <summary>
		/// Whether alpha coverage is enabled or not
		/// </summary>
		bool bAlphaToCoverageEnabled;

		/// <summary>
		/// The independent color target blending configuration
		/// </summary>
		Array<BlendingAttachmentDesc> Attachments;
	};
}