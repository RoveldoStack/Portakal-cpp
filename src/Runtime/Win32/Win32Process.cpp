#include "Win32Process.h"
#include <Runtime/Memory/Memory.h>

namespace Portakal
{
    Win32Process::Win32Process(const String& path, const Array<String>& cmdArguments) : PlatformProcess(path, cmdArguments), mHandle(NULL), mProcessInfo()
    {

    }
    void Win32Process::StartCore()
    {
        /*
        * Create information structure
        */
        STARTUPINFO startupInfo = {};

        Memory::Set(&startupInfo, 0, sizeof(STARTUPINFO));
        Memory::Set(&mProcessInfo, 0, sizeof(PROCESS_INFORMATION));

        /*
        * Create the proceess
        */
        CreateProcess(
            *GetPath(),
            (char*)*GetConcretedCommand(),
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &startupInfo,
            &mProcessInfo
        );

    }
    void Win32Process::WaitForFinishCore()
    {
        WaitForSingleObject(mProcessInfo.hProcess, INFINITE);
        CloseHandle(mProcessInfo.hProcess);
        CloseHandle(mProcessInfo.hThread);
    }
    void Win32Process::TerminateCore()
    {
        TerminateProcess(mProcessInfo.hProcess, 0);
        CloseHandle(mProcessInfo.hProcess);
        CloseHandle(mProcessInfo.hThread);
    }
    
}