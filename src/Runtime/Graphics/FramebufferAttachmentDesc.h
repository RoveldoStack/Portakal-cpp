#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class Texture;

	struct PORTAKAL_API FramebufferAttachmentDesc
	{
		FramebufferAttachmentDesc() : pTexture(nullptr),ArrayLayer(0),MipLevel(0)
		{

		}

		Texture* pTexture;
		unsigned int ArrayLayer;
		unsigned int MipLevel;
	};
}