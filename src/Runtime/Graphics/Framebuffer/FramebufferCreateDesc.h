#pragma once
#include <Runtime/Graphics/Framebuffer/FramebufferAttachmentDesc.h>
#include <Runtime/Containers/Array.h>

namespace Portakal
{
	/// <summary>
	/// Required information to create a framebuffer 
	/// </summary>
	struct PORTAKAL_API FramebufferCreateDesc
	{
		/// <summary>
		/// Color targets
		/// </summary>
		Array<FramebufferAttachmentDesc> ColorTargets;

		/// <summary>
		/// Depth stencil target
		/// </summary>
		FramebufferAttachmentDesc DepthStencilTarget;
	};
}