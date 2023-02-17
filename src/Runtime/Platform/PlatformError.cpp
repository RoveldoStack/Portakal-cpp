#include "PlatformError.h"

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Error.h>
typedef Portakal::Win32Error PlatformAbstraction;
#endif

namespace Portakal
{
	String PlatformError::GetCurrentError()
	{
		return PlatformAbstraction::GetCurrentError();
	}
}