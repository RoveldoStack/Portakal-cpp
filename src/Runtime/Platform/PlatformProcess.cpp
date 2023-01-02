#include "PlatformProcess.h"

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Process.h>
typedef Portakal::Win32Process PlatformAbstraction;
#endif

namespace Portakal
{
	PlatformProcess* PlatformProcess::Create(const String& path, const Array<String>& cmdArguments)
	{
		return new PlatformAbstraction(path,cmdArguments);
	}
	void PlatformProcess::Start()
	{
		StartCore();
		_active = true;
	}
	void PlatformProcess::End()
	{
		EndCore();
		_active = false;
	}

	PlatformProcess::PlatformProcess(const String& path, const Array<String>& cmdArguments)
	{
		_concretedCmdArguments = path;

		for (unsigned int i = 0; i < cmdArguments.GetCursor(); i++)
		{
			const String argument = cmdArguments[i];

			_concretedCmdArguments += " " + argument;
		}
	}
}