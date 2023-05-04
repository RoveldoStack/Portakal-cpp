#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class DomainFile;

	/// <summary>
	/// Represents a folder registered to the domain system
	/// </summary>
	class PORTAKAL_API DomainFolder
	{
	public:
		DomainFolder(DomainFolder* pParentFolder, const String& path);
		~DomainFolder();

		/// <summary>
		/// Returns the parent folder
		/// </summary>
		/// <returns></returns>
		FORCEINLINE DomainFolder* GetParentFolder() const noexcept { return mParentFolder; }

		/// <summary>
		/// Returns whether it's the root folder of the domain
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool IsRootFolder() const noexcept { return mParentFolder == nullptr; }

		/// <summary>
		/// Returns the files
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<DomainFile*> GetFiles() const noexcept { return mFiles; }

		/// <summary>
		/// Returns the sub folders
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<DomainFolder*> GetSubFolders() const noexcept { return mSubFolders; }

		/// <summary>
		/// Returns the folder path
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetFolderPath() const noexcept { return mPath; }

		/// <summary>
		/// Returns the folder name
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetFolderName() const noexcept { return mName; }

		/// <summary>
		/// Returns whether this domain folder is valid or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool IsValid() const noexcept { return mValid; }

		/// <summary>
		/// Creates a file from the source path
		/// </summary>
		/// <param name="sourceFilePath"></param>
		void CreateFileFromSource(const String& sourceFilePath);

		/// <summary>
		/// Creates anew file
		/// </summary>
		/// <param name="sourceFilePath"></param>
		/// <param name="type"></param>
		void CreateResourceFile(const String& name,const String& type);

		/// <summary>
		/// Creates a file descriptor
		/// </summary>
		/// <param name="name"></param>
		/// <param name="sourceFilePath"></param>
		/// <param name="resourceType"></param>
		void CreateFileDescriptor(const String& name, const String& sourceFilePath, const String& resourceType);

		/// <summary>
		/// Registeres file via descriptor
		/// </summary>
		/// <param name="descriptorFilePath"></param>
		/// <returns></returns>
		DomainFile* RegisterFileViaDescriptor(const String& descriptorFilePath);

		/// <summary>
		/// Deletes the file
		/// </summary>
		/// <param name="pFile"></param>
		void DeleteFile(DomainFile* pFile);

		/// <summary>
		/// Deletes this folder
		/// </summary>
		void Delete();

		/// <summary>
		/// Creates a folder
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		DomainFolder* CreateFolder(const String& name);

		/// <summary>
		/// Deletes the sub folder
		/// </summary>
		/// <param name="pFolder"></param>
		void DeleteSubFolder(DomainFolder* pFolder);
	private:

		/// <summary>
		/// Deletes the physical files
		/// </summary>
		/// <param name="pFile"></param>
		void DeleteFilePhysical(DomainFile* pFile);
	private:
		DomainFolder* mParentFolder;
		Array<DomainFile*> mFiles;
		Array<DomainFolder*> mSubFolders;
		String mName;
		String mPath;
		bool mValid;
	};
}