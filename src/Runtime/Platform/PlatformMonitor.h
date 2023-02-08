#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class Window;
	class PORTAKAL_API PlatformMonitor
	{
	public:
		static PlatformMonitor* GetFromWindow(Window* pWindow);
	public:
		FORCEINLINE virtual unsigned int GetWidth() const noexcept = 0;
		FORCEINLINE virtual unsigned int GetHeight() const noexcept = 0;

	};
}