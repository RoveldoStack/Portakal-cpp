#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	/// <summary>
	/// Platform agnostic directory util operations
	/// </summary>
	class PORTAKAL_API PlatformDirectory
	{
	public:
		PlatformDirectory() = delete;
		~PlatformDirectory() = delete;

		FORCEINLINE static bool Create(const String& path);
		FORCEINLINE static bool Delete(const String& path);
		FORCEINLINE static bool GetName(const String& path, String& nameOut);
		FORCEINLINE static bool GetFileNames(const String& path, Array<String>& namesOut);
		FORCEINLINE static bool GetFolderNames(const String& path, Array<String>& namesOut);
		FORCEINLINE static bool GetFileNamesViaExtension(const String& path, const String& extension, Array<String>& namesOut);
		FORCEINLINE static bool IsDirectoryExist(const String& path);
	};
}