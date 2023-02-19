#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/StandaloneGraphicsDeviceCreateDesc.h>
#include <Runtime/Graphics/WindowedGraphicsDeviceCreateDesc.h>

namespace Portakal
{
	/// <summary>
	/// Required information to create a graphics module
	/// </summary>
	struct PORTAKAL_API GraphicsModuleParams
	{
		/// <summary>
		/// Standalone device descriptions
		/// </summary>
		Array<StandaloneGraphicsDeviceCreateDesc> StandaloneDescs;

		/// <summary>
		/// Windowed device descriptions
		/// </summary>
		Array<WindowedGraphicsDeviceCreateDesc> WindowedDescs;
	};
}