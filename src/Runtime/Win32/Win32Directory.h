#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	/// <summary>
	/// Windows implementation of directory utility functions
	/// </summary>
	class PORTAKAL_API Win32Directory
	{
	public:
		Win32Directory() = delete;
		~Win32Directory() = delete;

		FORCEINLINE static bool Create(const String& path);
		FORCEINLINE static bool Delete(const String& path);
		FORCEINLINE static bool GetName(const String& path, String& nameOut);
		FORCEINLINE static bool GetFileNames(const String& path, Array<String>& namesOut);
		FORCEINLINE static bool GetFolderNames(const String& path, Array<String>& namesOut);
		FORCEINLINE static bool GetFileNamesViaExtension(const String& path, const String& extension, Array<String>& namesOut);
		FORCEINLINE static bool IsDirectoryExist(const String& path);
	};
}