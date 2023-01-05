#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/StandaloneGraphicsDeviceCreateDesc.h>
#include <Runtime/Graphics/WindowedGraphicsDeviceCreateDesc.h>

namespace Portakal
{
	struct PORTAKAL_API GraphicsModuleParams
	{
		Array<StandaloneGraphicsDeviceCreateDesc> StandaloneDescs;
		Array<WindowedGraphicsDeviceCreateDesc> WindowedDescs;
	};
}