#include "PlatformInfo.h"

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Info.h>
typedef Portakal::Win32Info PlatformAbstraction;
#endif

namespace Portakal
{
	unsigned int PlatformInfo::GetCpuThreadCount()
	{
		return PlatformAbstraction::GetCpuThreadCount();
	}
}