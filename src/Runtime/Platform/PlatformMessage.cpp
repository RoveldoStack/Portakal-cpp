#include "PlatformMessage.h"

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Message.h>
typedef Portakal::Win32Message PlatformAbstraction;
#endif

namespace Portakal
{
	void PlatformMessage::ShowMessageBox(const String& title,const String& message,const PlatformMessageBoxFlags flags)
	{
		PlatformAbstraction::ShowMessageBox(title, message,flags);
	}
}