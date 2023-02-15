#include "PlatformExplorer.h"

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Explorer.h>
typedef Portakal::Win32Explorer PlatformAbstraction;
#endif

namespace Portakal
{
	void PlatformExplorer::OpenExplorer(const String& directoryPath)
	{
		PlatformAbstraction::OpenExplorer(directoryPath);
	}
}