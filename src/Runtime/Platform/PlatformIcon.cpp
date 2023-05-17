#include "PlatformIcon.h"

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Icon.h>
typedef Portakal::Win32Icon PlatformAbstraction;
#endif
namespace Portakal
{
	void PlatformIcon::LoadIconFromPath(const String& path,Window* pTargetWindow)
	{
		PlatformAbstraction::LoadIconFromPath(path,pTargetWindow);
	}
}