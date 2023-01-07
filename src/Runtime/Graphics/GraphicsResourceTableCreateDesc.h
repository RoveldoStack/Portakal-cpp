#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/GraphicsDeviceObject.h>

namespace Portakal
{
	struct PORTAKAL_API GraphicsResourceTableCreateDesc
	{
		Array<GraphicsDeviceObject*> Resources;
	};
}