#pragma once
#include <Runtime/Graphics/FramebufferAttachmentDesc.h>
#include <Runtime/Containers/Array.h>

namespace Portakal
{
	struct PORTAKAL_API FramebufferCreateDesc
	{
		Array<FramebufferAttachmentDesc> ColorTargets;
		FramebufferAttachmentDesc DepthStencilTarget;
	};
}