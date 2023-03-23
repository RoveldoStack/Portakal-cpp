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
		mActive = true;
	}
	void PlatformProcess::Terminate()
	{
		TerminateCore();
		mActive = false;
	}

	void PlatformProcess::WaitForFinish()
	{
		WaitForFinishCore();
		mActive = false;
	}

	PlatformProcess::PlatformProcess(const String& path, const Array<String>& parameters) : mPath(path),mParameters(parameters)
	{
		mConcretedCommand = path;
		for (unsigned int i = 0; i < parameters.GetCursor(); i++)
		{
			const String argument = parameters[i];

			mConcretedCommand += " " + argument;
		}
	}
	PlatformProcess::~PlatformProcess()
	{
		if (mActive)
		{
			TerminateCore();
		}
		mActive = false;
	}
}