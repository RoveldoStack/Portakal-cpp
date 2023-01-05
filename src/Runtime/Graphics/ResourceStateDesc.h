#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/GraphicsResourceTableLayoutDesc.h>

namespace Portakal
{
	struct PORTAKAL_API ResourceStateDesc
	{
		Array<GraphicsResourceTableLayoutDesc> Slots;
	};
}