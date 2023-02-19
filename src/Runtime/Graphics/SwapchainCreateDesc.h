#pragma once
#include <Runtime/Graphics/TextureFormat.h>

namespace Portakal
{
	/// <summary>
	/// Required information to create swapchain
	/// </summary>
	struct PORTAKAL_API SwapchainCreateDesc
	{
		/// <summary>
		/// Target color format
		/// </summary>
		TextureFormat ColorFormat;

		/// <summary>
		/// Target deph stencil format
		/// </summary>
		TextureFormat DepthStencilFormat;

		/// <summary>
		/// The width
		/// </summary>
		unsigned int Width;

		/// <summary>
		/// The height
		/// </summary>
		unsigned int Height;

		/// <summary>
		/// The color buffer count
		/// </summary>
		unsigned int ColorBufferCount;
	};
}