#include "Win32Directory.h"
#include <comdef.h>
#include <Windows.h>
#include <mbstring.h>
#include <memory>
#include <string>
#include <system_error>
#include <Shlwapi.h>
#include <Runtime/Platform/PlatformFile.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
	bool Win32Directory::Create(const String& path)
	{
		if (IsDirectoryExist(path))
			return false;

		return CreateDirectoryA(*path, NULL);
	}
	bool Win32Directory::Delete(const String& path)
	{
		if (!IsDirectoryExist(path))
			return false;

		Array<String> subItems;
		GetFileNames(path, subItems);

		for (unsigned int i = 0; i < subItems.GetCursor(); i++)
		{
			const String itemPath = subItems[i];

			const bool bFile = IsDirectoryExist(itemPath);
			if (bFile)
			{
				PlatformFile::Delete(itemPath);
			}
			else
			{
				Delete(itemPath);
			}
		}
		LOG("Win32Directory", "Removed %d items from path %s", subItems.GetCursor(), *path);
		RemoveDirectoryA(*path);

		return true;
	}
	String Win32Directory::GetName(const String& path)
	{
		if (!IsDirectoryExist(path))
			return "";

		return PathFindFileNameA(*path);
	}
	bool Win32Directory::GetFileNames(const String& path, Array<String>& namesOut)
	{
		const String searchFilter = path + "*";

		WIN32_FIND_DATAA fileFindData = { 0 };

		const HANDLE fileHandle = FindFirstFileA(*searchFilter, &fileFindData);
		if (fileHandle == INVALID_HANDLE_VALUE)
		{
			FindClose(fileHandle);
			return false;
		}
		do
		{
			const String folderName = fileFindData.cFileName;
			if (folderName == "." || folderName == "..")
				continue;

			namesOut.Add(path + folderName);

		} while (FindNextFileA(fileHandle, &fileFindData));

		return true;
	}
	bool Win32Directory::GetFolderNames(const String& path, Array<String>& namesOut)
	{
		if (!IsDirectoryExist(path))
			return false;

		Array<String> items;
		GetFileNames(path, items);

		for (unsigned int i = 0; i < items.GetCursor(); i++)
		{
			if (IsDirectoryExist(items[i]))
			{
				namesOut.Add(items[i]);
			}
		}

		return true;
	}
	bool Win32Directory::GetFileNamesViaExtension(const String& path, const String& extension, Array<String>& namesOut)
	{
		if (!IsDirectoryExist(path))
			return false;

		Array<String> files;
		GetFileNames(path, files);

		for (unsigned int i = 0; i < files.GetCursor(); i++)
		{
			const String file = files[i];

			if (!PlatformFile::IsExist(file))
				continue;

			const String fileExtension = PlatformFile::GetExtension(file);
			

			if (fileExtension == extension)
				namesOut.Add(file);
		}
	}
	bool Win32Directory::IsDirectoryExist(const String& path)
	{
		const DWORD diagnostic = GetFileAttributesA(*path);

		if (diagnostic != INVALID_FILE_ATTRIBUTES && diagnostic == FILE_ATTRIBUTE_DIRECTORY)
			return true;

		return false;
	}
}