#include "PlatformCriticalSection.h"

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32CriticalSection.h>
typedef Portakal::Win32CriticalSection PlatfromAbstraction;
#endif

namespace Portakal
{
	PlatformCriticalSection* PlatformCriticalSection::Create()
	{
		return new PlatfromAbstraction();
	}
}