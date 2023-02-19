#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class Window;
	class GraphicsDevice;

	/// <summary>
	/// Utility adapter for binding a device and a window together
	/// </summary>
	class WindowChildDeviceAdapter
	{
	public:
		WindowChildDeviceAdapter() = delete;
		~WindowChildDeviceAdapter() = delete;

		/// <summary>
		/// Internal device binding method
		/// </summary>
		/// <param name="pWindow"></param>
		/// <param name="pDevice"></param>
		static void _BindDeviceAndWindow(Window* pWindow, GraphicsDevice* pDevice);
	};
}