#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Memory/ByteBlock.h>

namespace Portakal
{
	/// <summary>
	/// Platform agnostic file management class
	/// </summary>
	class PORTAKAL_API PlatformFile
	{
	public:
		PlatformFile() = delete;
		~PlatformFile() = delete;

		/// <summary>
		/// Returns whether the file exists or not
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static bool IsExist(const String& path);

		/// <summary>
		/// Creates anew file
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static bool Create(const String& path);

		/// <summary>
		/// Deletes the existing file
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static bool Delete(const String& path);

		/// <summary>
		/// Writes the given string content into file
		/// </summary>
		/// <param name="path"></param>
		/// <param name="content"></param>
		/// <param name="offset"></param>
		/// <returns></returns>
		FORCEINLINE static bool Write(const String& path, const String& content, const unsigned long long offset = 0);

		/// <summary>
		/// Writes the given byteblock content into file
		/// </summary>
		/// <param name="path"></param>
		/// <param name="block"></param>
		/// <param name="offset"></param>
		/// <returns></returns>
		FORCEINLINE static bool Write(const String& path, const ByteBlock& block, const unsigned long long offset = 0);

		/// <summary>
		/// Reads the file into a string
		/// </summary>
		/// <param name="path"></param>
		/// <param name="contentOut"></param>
		/// <param name="startIndex"></param>
		/// <param name="endIndex"></param>
		/// <returns></returns>
		FORCEINLINE static bool Read(const String& path, String& contentOut, const unsigned long long startIndex = 0, const unsigned long long endIndex = 0);

		/// <summary>
		/// Reads the file into a byteblock
		/// </summary>
		/// <param name="path"></param>
		/// <param name="block"></param>
		/// <param name="startIndex"></param>
		/// <param name="endIndex"></param>
		/// <returns></returns>
		FORCEINLINE static bool Read(const String& path, ByteBlock& block, const unsigned long long startIndex = 0, const unsigned long long endIndex = 0);

		/// <summary>
		/// Copies the files
		/// </summary>
		/// <param name="targetPath"></param>
		/// <param name="sourcePath"></param>
		/// <returns></returns>
		FORCEINLINE static bool Copy(const String& targetPath, const String& sourcePath);

		/// <summary>
		/// Returns the file size
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static unsigned long long GetSize(const String& path);

		/// <summary>
		/// Returns the file extension
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static String GetExtension(const String& path);

		/// <summary>
		/// Removes the file extension
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static bool RemoveExtension(String& path);

		/// <summary>
		/// Returns the name of the file with extension
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static String GetName(const String& path);

		/// <summary>
		/// Returns the name of the file without extension
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static String GetNameWithoutExtension(const String& path);

		/// <summary>
		/// Returns the file directory
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		FORCEINLINE static String GetFileDirectory(const String& path);
	};
}