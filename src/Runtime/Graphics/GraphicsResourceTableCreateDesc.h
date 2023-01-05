#pragma once
#include <Runtime/Graphics/GraphicsResourceTableTarget.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/GraphicsDeviceObject.h>

namespace Portakal
{
	struct PORTAKAL_API GraphicsResourceTableCreateDesc
	{
		GraphicsResourceTableTarget Target;
		Array<GraphicsDeviceObject*> Resources;
	};
}