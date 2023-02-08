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
    bool PlatformFile::Copy(const String& targetPath, const String& sourcePath)
    {
        return PlatformAbstraction::Copy(targetPath,sourcePath);
    }
    unsigned long long PlatformFile::GetSize(const String& path)
    {
        unsigned long long output = 0;
        if (PlatformAbstraction::GetSize(path, output))
            return output;
        return 0;
    }
    String PlatformFile::GetExtension(const String& path)
    {
        String output;
        if (PlatformAbstraction::GetExtension(path, output))
            return output;
        return "";
    }
    bool PlatformFile::RemoveExtension(String& path)
    {
        return PlatformAbstraction::RemoveExtension(path);;
    }
    String PlatformFile::GetName(const String& path)
    {
        String output;
        if (PlatformAbstraction::GetName(path, output))
            return output;
        return "";
    }
    String PlatformFile::GetNameWithoutExtension(const String& path)
    {
        String name = PlatformFile::GetName(path);
        
        RemoveExtension(name);

        return name;
    }
    String PlatformFile::GetFileDirectory(const String& path)
    {
        String name = PlatformFile::GetName(path);

        String output = path;
        output -= "\\" + name;

        return output;
    }
}