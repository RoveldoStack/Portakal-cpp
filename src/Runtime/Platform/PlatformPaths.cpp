#include "PlatformPaths.h"

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Paths.h>
typedef Portakal::Win32Paths PlatformAbstraction;
#endif

namespace Portakal
{
	String PlatformPaths::GetApplicationLoadPath()
	{
		return PlatformAbstraction::GetApplicationLoadPath();
	}
}