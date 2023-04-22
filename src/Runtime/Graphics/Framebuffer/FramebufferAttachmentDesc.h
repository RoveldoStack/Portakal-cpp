#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class Texture;

	/// <summary>
	/// Required information to configure a framebuffer attachment
	/// </summary>
	struct PORTAKAL_API FramebufferAttachmentDesc
	{
		FramebufferAttachmentDesc() : pTexture(nullptr),ArrayLayer(0),MipLevel(0)
		{

		}

		/// <summary>
		/// The target texture with a RenderTarget or DepthStencil flag enabled
		/// </summary>
		Texture* pTexture;

		/// <summary>
		/// Texture array index
		/// </summary>
		unsigned int ArrayLayer;

		/// <summary>
		/// Texture mip index
		/// </summary>
		unsigned int MipLevel;
	};
}