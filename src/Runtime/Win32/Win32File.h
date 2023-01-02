#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Memory/ByteBlock.h>

namespace Portakal
{
	/// <summary>
	/// Windows implementation of file utility class
	/// </summary>
	class PORTAKAL_API Win32File
	{
	public:
		Win32File() = delete;
		~Win32File() = delete;

		FORCEINLINE static bool IsFileExist(const String& path);
		FORCEINLINE static bool Create(const String& path);
		FORCEINLINE static bool Delete(const String& path);
		FORCEINLINE static bool Write(const String& path, const String& content, const unsigned long long offset);
		FORCEINLINE static bool Write(const String& path, const ByteBlock& block, const unsigned long long offset);
		FORCEINLINE static bool Read(const String& path, String& contentOut, const unsigned long long startIndex = 0, const unsigned long long endIndex = 0);
		FORCEINLINE static bool Read(const String& path, ByteBlock& block, const unsigned long long startIndex = 0, const unsigned long long endIndex = 0);
		FORCEINLINE static bool GetSize(const String& path, unsigned long long& sizeOut);
		FORCEINLINE static bool GetExtension(const String& path, String& extensionOut);
		FORCEINLINE static bool GetName(const String& path, String& nameOut);
		FORCEINLINE static bool RemoveExtension(String& path);
	};
}