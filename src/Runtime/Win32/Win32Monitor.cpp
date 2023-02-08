#include "Win32Monitor.h"
#include <Runtime/Win32/Win32Window.h>

namespace Portakal
{
	Win32Monitor::Win32Monitor(Window* pWindow)
	{
		const Win32Window* pWin32Window = (const Win32Window*)pWindow;

		HMONITOR handle = MonitorFromWindow(pWin32Window->GetWin32WindowHandle(), MONITOR_DEFAULTTONEAREST);
		MONITORINFO info = {};
		info.cbSize = sizeof(MONITORINFO);
		GetMonitorInfo(handle, &info);

		mHandle = handle;
		mInfo = info;
	}
	Win32Monitor::~Win32Monitor()
	{
		mHandle = NULL;
		mInfo = {};
	}
	unsigned int Win32Monitor::GetWidth() const noexcept
	{
		return mInfo.rcMonitor.right - mInfo.rcMonitor.left;
	}
	unsigned int Win32Monitor::GetHeight() const noexcept
	{
		return mInfo.rcMonitor.bottom - mInfo.rcMonitor.top;
	}
}