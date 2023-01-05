#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/BlendingAttachmentDesc.h>

namespace Portakal
{
	struct PORTAKAL_API BlendingStateDesc
	{
		float BlendFactor;
		Array<BlendingAttachmentDesc> Attachments;
		bool bAlphaToCoverageEnabled;
	};
}