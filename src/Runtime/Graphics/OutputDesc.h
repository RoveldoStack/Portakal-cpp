#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/OutputAttachmentDesc.h>

namespace Portakal
{
	/// <summary>
	/// Required information specify the output description for the pipeline's output merger
	/// </summary>
	struct PORTAKAL_API OutputDesc
	{
		/// <summary>
		/// The color targets of the output
		/// </summary>
		Array<OutputAttachmentDesc> ColorAttachments;

		/// <summary>
		/// The depth stencil target of the output
		/// </summary>
		OutputAttachmentDesc DepthStencilAttachment;

		/// <summary>
		/// The sample count
		/// </summary>
		unsigned char SampleCount;
	};
}