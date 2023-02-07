#include "DomainFolder.h"
#include <Runtime/Platform/PlatformDirectory.h>
#include <Runtime/Log/Log.h>
#include <Runtime/Platform/PlatformMessage.h>
#include <Editor/Domain/DomainFileDescriptorYamlSerialize.h>
#include <Runtime/Yaml/Yaml.h>
#include <Runtime/Platform/PlatformFile.h>
namespace Portakal
{
	DomainFolder::DomainFolder(DomainFolder* pParentFolder, const String& path) : mParentFolder(nullptr)
	{
		/*
		* Validate the directory
		*/
		if (!PlatformDirectory::IsDirectoryExist(path))
		{
			PlatformMessage::ShowMessageBox("Domain Folder", "The path is missing! : " + path);
			return;
		}

		/*
		* Setup
		*/
		mParentFolder = pParentFolder;
		mPath = path;
		PlatformDirectory::GetName(path, mName);

		/*
		* Collect files
		*/
		Array<String> files;
		PlatformDirectory::GetFileNamesViaExtension(path, ".pid", files);
		for (unsigned int i = 0; i < files.GetCursor(); i++)
		{
			const String filePath = files[i];
			String fileDescriptorContent;
			PlatformFile::Read(filePath, fileDescriptorContent);

			DomainFileDescriptor fileDescriptor = {};
			Yaml::ToObject(fileDescriptorContent, &fileDescriptor);
		}

		/*
		* Collect folders
		*/
		Array<String> folders;
		PlatformDirectory::GetFolderNames(path + "\\", folders);
		for (unsigned int i = 0; i < folders.GetCursor(); i++)
		{
			const String folderPath = folders[i];
			DomainFolder* pFolder = new DomainFolder(this,folderPath);
			mSubFolders.Add(pFolder);
		}
	}
	DomainFolder::~DomainFolder()
	{
		/*
		* Delete file entries
		*/
		for (unsigned int i = 0; i < mFiles.GetCursor(); i++)
		{
			delete mFiles[i];
		}
		mFiles.Clear();

		/*
		* Delete folder entries
		*/
		for (unsigned int i = 0; i < mSubFolders.GetCursor(); i++)
		{
			delete mSubFolders[i];
		}
		mSubFolders.Clear();
	}
}