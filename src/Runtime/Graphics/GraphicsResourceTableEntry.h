#pragma once
#include <Runtime/Graphics/GraphicsResourceType.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	struct PORTAKAL_API GraphicsResourceTableEntry
	{
		String Name;
		GraphicsResourceType Type;
	};
}