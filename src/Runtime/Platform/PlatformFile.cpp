#include "PlatformFile.h"

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32File.h>
typedef Portakal::Win32File PlatformAbstraction;
#endif

namespace Portakal
{
    bool PlatformFile::IsExist(const String& path)
    {
        return PlatformAbstraction::IsFileExist(path);
    }
    bool PlatformFile::Create(const String& path)
    {
        return PlatformAbstraction::Create(path);
    }
    bool PlatformFile::Delete(const String& path)
    {
        return PlatformAbstraction::Delete(path);
    }
    bool PlatformFile::Write(const String& path, const String& content, const unsigned long long offset)
    {
        return PlatformAbstraction::Write(path, content, offset);
    }
    bool PlatformFile::Write(const String& path, const ByteBlock& block, const unsigned long long offset)
    {
        return PlatformAbstraction::Write(path, block, offset);
    }
    bool PlatformFile::Read(const String& path, String& contentOut, const unsigned long long startIndex, const unsigned long long endIndex)
    {
        return PlatformAbstraction::Read(path, contentOut, startIndex, endIndex);
    }
    bool PlatformFile::Read(const String& path, ByteBlock& block, const unsigned long long startIndex, const unsigned long long endIndex)
    {
        return PlatformAbstraction::Read(path, block, startIndex, endIndex);
    }
    bool PlatformFile::GetSize(const String& path, unsigned long long& sizeOut)
    {
        return PlatformAbstraction::GetSize(path, sizeOut);
    }
    bool PlatformFile::GetExtension(const String& path, String& extensionOut)
    {
        return PlatformAbstraction::GetExtension(path, extensionOut);
    }
    bool PlatformFile::RemoveExtension(String& path)
    {
        return PlatformAbstraction::RemoveExtension(path);;
    }
    bool PlatformFile::GetName(const String& path, String& nameOut)
    {
        return PlatformAbstraction::GetName(path, nameOut);
    }
    bool PlatformFile::GetNameWithoutExtension(const String& path, String& nameOut)
    {
        String name;
        PlatformFile::GetName(path, name);
        RemoveExtension(name);

        nameOut = name;

        return true;
    }
    bool PlatformFile::GetFileDirectory(const String& path, String& folderOut)
    {
        folderOut = path;

        String name;
        PlatformFile::GetName(path, name);

        folderOut -= "/" + name;

        return true;
    }
}