#include "PlatformDirectory.h"

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Directory.h>
typedef Portakal::Win32Directory PlatformAbstraction;
#endif

namespace Portakal
{
    bool PlatformDirectory::Create(const String& path)
    {
        return PlatformAbstraction::Create(path);
    }
    bool PlatformDirectory::Delete(const String& path)
    {
        return PlatformAbstraction::Delete(path);
    }
    String PlatformDirectory::GetName(const String& path)
    {
        return PlatformAbstraction::GetName(path);
    }
    bool PlatformDirectory::GetFileNames(const String& path, Array<String>& namesOut)
    {
        return PlatformAbstraction::GetFileNames(path, namesOut);
    }
    bool PlatformDirectory::GetFolderNames(const String& path, Array<String>& namesOut)
    {
        return PlatformAbstraction::GetFolderNames(path, namesOut);
    }
    bool PlatformDirectory::GetFileNamesViaExtension(const String& path, const String& extension, Array<String>& namesOut)
    {
        return PlatformAbstraction::GetFileNamesViaExtension(path, extension, namesOut);
    }
    bool PlatformDirectory::IsDirectoryExist(const String& path)
    {
        return PlatformAbstraction::IsDirectoryExist(path);
    }
}