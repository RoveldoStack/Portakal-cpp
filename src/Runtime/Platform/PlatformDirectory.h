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

		/// <summary>
		/// Creats anew directory
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static bool Create(const String& path);

		/// <summary>
		/// Deletes the existing directory
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static bool Delete(const String& path);

		/// <summary>
		/// Returns the folder name of the directory
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static String GetName(const String& path);

		/// <summary>
		/// Returns the files in the directory
		/// </summary>
		/// <param name="path"></param>
		/// <param name="namesOut"></param>
		/// <returns></returns>
		FORCEINLINE static bool GetFileNames(const String& path, Array<String>& namesOut);

		/// <summary>
		/// Returns the folders in the directory
		/// </summary>
		/// <param name="path"></param>
		/// <param name="namesOut"></param>
		/// <returns></returns>
		FORCEINLINE static bool GetFolderNames(const String& path, Array<String>& namesOut);

		/// <summary>
		/// Returns the files with a extension filter
		/// </summary>
		/// <param name="path"></param>
		/// <param name="extension"></param>
		/// <param name="namesOut"></param>
		/// <returns></returns>
		FORCEINLINE static bool GetFileNamesViaExtension(const String& path, const String& extension, Array<String>& namesOut);

		/// <summary>
		/// Returns whether the given directory exists or not
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static bool IsDirectoryExist(const String& path);
	};
}