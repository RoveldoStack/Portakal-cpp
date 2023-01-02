#include "Win32Process.h"
#include <Runtime/Memory/Memory.h>

namespace Portakal
{
    Win32Process::~Win32Process()
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
            (char*)*GetConcretedCmdArguments(),
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
    void Win32Process::EndCore()
    {
        CloseHandle(mProcessInfo.hProcess);
        CloseHandle(mProcessInfo.hThread);
    }
}