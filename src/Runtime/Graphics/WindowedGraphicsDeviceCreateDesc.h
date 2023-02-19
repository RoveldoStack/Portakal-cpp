#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Graphics/GraphicsBackend.h>
#include <Runtime/Graphics/TextureFormat.h>

namespace Portakal
{
	class Window;

	/// <summary>
	/// Required information to create a windowed graphics device
	/// </summary>
	struct PORTAKAL_API WindowedGraphicsDeviceCreateDesc
	{
		/// <summary>
		/// The target owner window
		/// </summary>
		Window* pOwnerWindow;

		/// <summary>
		/// Requested backend
		/// </summary>
		GraphicsBackend Backend;

		/// <summary>
		/// Swapchain color format
		/// </summary>
		TextureFormat ColorFormat;

		/// <summary>
		/// Swapchain depth stencil format
		/// </summary>
		TextureFormat DepthStencilFormat;

		/// <summary>
		/// Swapchain color buffer count
		/// </summary>
		unsigned char BufferCount;
	};
}