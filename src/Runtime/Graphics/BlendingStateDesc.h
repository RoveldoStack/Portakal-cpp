#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/BlendingAttachmentDesc.h>

namespace Portakal
{
	struct PORTAKAL_API BlendingStateDesc
	{
		bool bAlphaToCoverageEnabled;
		Array<BlendingAttachmentDesc> Attachments;

	};
}