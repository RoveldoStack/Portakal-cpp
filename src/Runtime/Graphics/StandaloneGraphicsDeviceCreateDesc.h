#pragma once
#include <Runtime/Graphics/GraphicsBackend.h>

namespace Portakal
{
	/// <summary>
	/// Required information to specift a standalone graphics device
	/// </summary>
	struct PORTAKAL_API StandaloneGraphicsDeviceCreateDesc
	{
		GraphicsBackend Backend;
	};
}