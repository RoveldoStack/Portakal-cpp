#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/OutputAttachmentDesc.h>

namespace Portakal
{
	struct PORTAKAL_API OutputDesc
	{
		Array<OutputAttachmentDesc> ColorAttachments;
		OutputAttachmentDesc DepthStencilAttachment;
		unsigned char SampleCount;
	};
}