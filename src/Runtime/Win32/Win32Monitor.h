#pragma once
#include <Runtime/Platform/PlatformMonitor.h>
#include <Windows.h>

namespace Portakal
{
	class PORTAKAL_API Win32Monitor : public PlatformMonitor
	{
	public:
		Win32Monitor(Window* pWindow);
		~Win32Monitor();
		FORCEINLINE unsigned int GetWidth() const noexcept override;
		FORCEINLINE unsigned int GetHeight() const noexcept override;
	private:
		HMONITOR mHandle;
		MONITORINFO mInfo;
	};
}