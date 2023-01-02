#pragma once
#include <Runtime/Platform/PlatformProcess.h>
#include <Windows.h>

namespace Portakal
{
	class PORTAKAL_API Win32Process final : public PlatformProcess
	{
	public:
		Win32Process(const String & path, const Array<String>&cmdArguments) : PlatformProcess(path,cmdArguments) {}
		~Win32Process();
	protected:
		// Inherited via PlatformProcess
		virtual void StartCore() override;
		virtual void EndCore() override;

	private:
		HANDLE mHandle;
		PROCESS_INFORMATION mProcessInfo;
	};
}