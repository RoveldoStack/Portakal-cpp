#pragma once
#include <Runtime/Graphics/Texture/TextureFormat.h>

namespace Portakal
{
	/// <summary>
	/// Required information to specify an output target description for pipeline's output merger
	/// </summary>
	struct PORTAKAL_API OutputAttachmentDesc
	{
		TextureFormat Format;
	};
}