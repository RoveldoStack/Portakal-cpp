#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class DomainFile;
	class PORTAKAL_API DomainFolder
	{
	public:
		DomainFolder(DomainFolder* pParentFolder, const String& path);
		~DomainFolder();

		FORCEINLINE DomainFolder* GetParentFolder() const noexcept { return mParentFolder; }
		FORCEINLINE bool IsRootFolder() const noexcept { return mParentFolder == nullptr; }
		FORCEINLINE Array<DomainFile*> GetFiles() const noexcept { return mFiles; }
		FORCEINLINE Array<DomainFolder*> GetSubFolders() const noexcept { return mSubFolders; }
		FORCEINLINE String GetFolderPath() const noexcept { return mPath; }
		FORCEINLINE String GetFolderName() const noexcept { return mName; }

		void CreateFileFromSource(const String& sourceFilePath);
		void CreateFileDescriptor(const String& name, const String& sourceFilePath, const String& resourceType);
		void CreateFolder(const String& name);
		DomainFile* RegisterFileViaDescriptor(const String& descriptorFilePath);
	private:
		DomainFolder* mParentFolder;
		Array<DomainFile*> mFiles;
		Array<DomainFolder*> mSubFolders;
		String mName;
		String mPath;
	};
}