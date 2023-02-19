#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class Window;

	/// <summary>
	/// Platform agnostic monitor interface
	/// </summary>
	class PORTAKAL_API PlatformMonitor
	{
	public:
		/// <summary>
		/// Creates a monitor interface via a window
		/// </summary>
		/// <param name="pWindow"></param>
		/// <returns></returns>
		static PlatformMonitor* GetFromWindow(Window* pWindow);
	public:

		/// <summary>
		/// Returns the width of the window
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual unsigned int GetWidth() const noexcept = 0;

		/// <summary>
		/// Returns the height of the window
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual unsigned int GetHeight() const noexcept = 0;

	};
}