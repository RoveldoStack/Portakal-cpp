#include "Win32Explorer.h"
#include <Windows.h>
#include <shellapi.h>

namespace Portakal
{
	void Win32Explorer::OpenExplorer(const String& directoryPath)
	{
		ShellExecute(NULL, "open", *directoryPath, NULL, NULL, SW_SHOWDEFAULT);
	}
}