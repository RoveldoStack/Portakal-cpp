#include "PlatformLibrary.h"
#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Library.h>
typedef Portakal::Win32Library PlatformAbstraction;
#endif
namespace Portakal
{
	PlatformLibrary* PlatformLibrary::Create(const String& path)
	{
		return new PlatformAbstraction(path);
	}
}