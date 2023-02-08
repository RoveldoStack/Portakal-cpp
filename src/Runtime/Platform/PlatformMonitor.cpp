#include "PlatformMonitor.h"

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Monitor.h>
typedef Portakal::Win32Monitor PlatformAbstraction;
#endif

namespace Portakal
{
	PlatformMonitor* PlatformMonitor::GetFromWindow(Window* pWindow)
	{
		return new PlatformAbstraction(pWindow);
	}
}