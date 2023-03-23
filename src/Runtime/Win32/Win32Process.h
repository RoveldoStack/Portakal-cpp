#pragma once
#include <Runtime/Platform/PlatformProcess.h>
#include <Windows.h>

namespace Portakal
{
	class PORTAKAL_API Win32Process final : public PlatformProcess
	{
	public:
		Win32Process(const String& path, const Array<String>& cmdArguments);
		~Win32Process() = default;
	protected:
		// Inherited via PlatformProcess
		virtual void StartCore() override;
		virtual void WaitForFinishCore() override;
		virtual void TerminateCore() override;

	private:
		HANDLE mHandle;
		PROCESS_INFORMATION mProcessInfo;


	};
}