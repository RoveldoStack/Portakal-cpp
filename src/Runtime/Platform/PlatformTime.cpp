#include "PlatformTime.h"

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Time.h>
typedef Portakal::Win32Time PlatformAbstraction;
#endif

namespace Portakal
{
    unsigned long long PlatformTime::GetCurrentTimeAsNanoseconds()
    {
        return PlatformAbstraction::GetCurrentTimeAsNanoseconds();
    }
}