#include "Win32File.h"
#include <Windows.h>
#include <Shlwapi.h>
#include <stdio.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
	unsigned long g_TransferredBytes;
	VOID CALLBACK FileIOCompletionRoutine(
		__in  DWORD dwErrorCode,
		__in  DWORD dwNumberOfBytesTransfered,
		__in  LPOVERLAPPED lpOverlapped
	);
	VOID CALLBACK FileIOCompletionRoutine(
		__in  DWORD dwErrorCode,
		__in  DWORD dwNumberOfBytesTransfered,
		__in  LPOVERLAPPED lpOverlapped)
	{
		g_TransferredBytes = dwNumberOfBytesTransfered;
	}

	bool Win32File::IsFileExist(const String& path)
	{
		const DWORD diagnostic = GetFileAttributesA(*path);
		if (diagnostic == INVALID_FILE_ATTRIBUTES || diagnostic == FILE_ATTRIBUTE_DIRECTORY)
			return false;

		return true;
	}

	bool Win32File::Create(const String& path)
	{
		const bool fileExists = IsFileExist(path);
		if (fileExists) // try delete file
		{
			Delete(path);
		}

		const HANDLE fileHandle = CreateFileA(*path, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (fileHandle)
			CloseHandle(fileHandle);

		return fileHandle != nullptr;
	}
	bool Win32File::Delete(const String& path)
	{
		if (IsFileExist(*path))
			return DeleteFileA(*path);
	}
	bool Win32File::Write(const String& path, const String& content, const unsigned long long offset)
	{
		HANDLE fileHandle = NULL;
		if (IsFileExist(path)) // overwrite
		{
			fileHandle = CreateFileA(*path, GENERIC_WRITE,
				0,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
		}
		else // create new file and write
		{
			fileHandle = CreateFileA(*path, GENERIC_WRITE,
				0,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
		}

		unsigned long writtenBytes = 0;

		const bool writeSuccess = WriteFile(fileHandle, content.GetSource(), content.GetCursor(), &writtenBytes, NULL);
		if (!writeSuccess)
			return false;

		CloseHandle(fileHandle);

		return true;
	}
	bool Win32File::Write(const String& path, const ByteBlock& block, const unsigned long long offset)
	{
		HANDLE fileHandle = NULL;
		if (IsFileExist(path)) // overwrite
		{
			fileHandle = CreateFileA(*path, GENERIC_WRITE,
				0,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
		}
		else // create new file and write
		{
			fileHandle = CreateFileA(*path, GENERIC_WRITE,
				0,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
		}

		unsigned long writtenBytes = 0;

		const bool writeSuccess = WriteFile(fileHandle, block.GetBlockDataPtr(), block.GetBlockSizeInBytes(), &writtenBytes, NULL);
		if (!writeSuccess)
			return false;

		CloseHandle(fileHandle);
	}
	bool Win32File::Read(const String& path, String& contentOut, const unsigned long long startIndex, const unsigned long long endIndex)
	{
		if (!IsFileExist(path))
			return false;

		unsigned long long fileSize = 0;
		GetSize(path, fileSize);


		const unsigned long expectedReadInterval = endIndex == 0 ? fileSize : endIndex - startIndex;
		if (fileSize <= 0 || expectedReadInterval > fileSize)
			return false;

		LOG("Read", "Attempt start %d, end %d, total %d", startIndex, endIndex, expectedReadInterval);

		unsigned long numberOfBytesRead = 0;
		OVERLAPPED overlappedData = { 0 };

		const HANDLE fileHandle = CreateFileA(*path, GENERIC_READ, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
		if (!fileHandle)
			return false;

		unsigned char* readBuffer = new unsigned char[expectedReadInterval];
		const bool readSuccess = ReadFileEx(fileHandle, readBuffer, expectedReadInterval, &overlappedData, FileIOCompletionRoutine);

		if (!readSuccess)
			return false;

		contentOut = String((char*)readBuffer, expectedReadInterval);

		CloseHandle(fileHandle);

		return true;
	}
	bool Win32File::Read(const String& path, ByteBlock& block, const unsigned long long startIndex, const unsigned long long endIndex)
	{
		/*
		* Validate file
		*/
		if (!IsFileExist(path))
			return false;

		/*
		* Get file size and validate read interval
		*/
		unsigned long long fileSize = 0;
		GetSize(path, fileSize);
		if (fileSize == 0)
			return true;

		const unsigned long expectedReadInterval = endIndex == 0 ? fileSize : endIndex - startIndex;
		if (fileSize <= 0 || expectedReadInterval > fileSize)
			return false;

		/*
		* Open file for reading
		*/
		unsigned long numberOfBytesRead = 0;
		OVERLAPPED overlappedData = { 0 };

		const HANDLE fileHandle = CreateFileA(*path, GENERIC_READ, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

		/*
		* Validate file handle
		*/
		if (!fileHandle)
			return false;

		/*
		* Read the file
		*/
		unsigned char* readBuffer = new unsigned char[expectedReadInterval];

		const bool readSuccess = ReadFileEx(fileHandle, readBuffer, expectedReadInterval, &overlappedData, FileIOCompletionRoutine);

		if (!readSuccess)
			return false;

		block.Copy(readBuffer, expectedReadInterval);

		delete[] readBuffer;

		CloseHandle(fileHandle);

		return true;
	}
	bool Win32File::Copy(const String& targetPath, const String& sourcePath)
	{
		return CopyFile(*sourcePath, *targetPath, TRUE);
	}
	bool Win32File::GetSize(const String& path, unsigned long long& sizeOut)
	{
		const HANDLE fileHandle = CreateFileA(*path,
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (!fileHandle)
			return false;

		sizeOut = GetFileSize(fileHandle, NULL);

		CloseHandle(fileHandle);

		return true;
	}
	bool Win32File::GetExtension(const String& path, String& extensionOut)
	{
		if (!IsFileExist(path))
			return false;

		extensionOut = PathFindExtensionA(*path);

		return true;
	}
	bool Win32File::GetName(const String& path, String& nameOut)
	{
		const char* pData = PathFindFileNameA(*path);
		nameOut = pData;
		return true;
	}
	bool Win32File::RemoveExtension(String& path)
	{
		char* pData = path.GetSourceCopy();
		PathRemoveExtension(pData);

		path = pData;
		return true;
	}
}