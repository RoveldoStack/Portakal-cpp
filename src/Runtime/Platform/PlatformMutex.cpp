#include "PlatformMutex.h"

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Mutex.h>
typedef Portakal::Win32Mutex PlatformAbstraction;
#endif

namespace Portakal
{
	PlatformMutex* PlatformMutex::Create()
	{
		return new PlatformAbstraction();
	}
}