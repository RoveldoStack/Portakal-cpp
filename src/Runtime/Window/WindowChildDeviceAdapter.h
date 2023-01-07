#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class Window;
	class GraphicsDevice;

	class WindowChildDeviceAdapter
	{
	public:
		WindowChildDeviceAdapter() = delete;
		~WindowChildDeviceAdapter() = delete;

		static void _BindDeviceAndWindow(Window* pWindow, GraphicsDevice* pDevice);
	};
}