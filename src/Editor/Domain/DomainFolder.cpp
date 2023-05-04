#include "DomainFolder.h"
#include <Runtime/Platform/PlatformDirectory.h>
#include <Runtime/Log/Log.h>
#include <Runtime/Platform/PlatformMessage.h>
#include <Editor/Domain/DomainFileDescriptorYamlSerializer.h>
#include <Runtime/Yaml/Yaml.h>
#include <Runtime/Platform/PlatformFile.h>
#include <Editor/Asset/IAssetSerializer.h>
#include <Editor/Asset/CustomAssetSerializerAttribute.h>
#include <Editor/Domain/DomainFile.h>
#include <Editor/Asset/CustomAssetImporterAttribute.h>
#include <Editor/Asset/IAssetImporter.h>
#include <Editor/Asset/Importers/SimpleTextAssetImporter.h>
#include <Editor/Asset/Importers/SimpleTextAssetImporter2.h>
namespace Portakal
{
	DomainFolder::DomainFolder(DomainFolder* pParentFolder, const String& path) : mParentFolder(nullptr),mValid(false)
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
		mName = PlatformDirectory::GetName(path);

		/*
		* Collect files
		*/
		Array<String> files;
		PlatformDirectory::GetFileNamesViaExtension(path + "\\", ".fd", files);
		for (unsigned int i = 0; i < files.GetCursor(); i++)
		{
			/*
			* Read domain file descriptor
			*/
			const String filePath = files[i];

			/*
			* Create domain file
			*/
			DomainFile* pFile = new DomainFile(filePath, this);

			/*
			* Validate if domain file is valid
			*/
			if (!pFile->IsValid())
			{
				delete pFile;
				continue;
			}

			/*
			* Register domain file
			*/
			mFiles.Add(pFile);
		}

		/*
		* Collect folders
		*/
		Array<String> folders;
		PlatformDirectory::GetFolderNames(path + "\\", folders);
		for (unsigned int i = 0; i < folders.GetCursor(); i++)
		{
			const String folderPath = folders[i];

			/*
			* Try create domain file
			*/
			DomainFolder* pFolder = new DomainFolder(this,folderPath);

			/*
			* Validate domain folder
			*/
			if (!pFolder->IsValid())
			{
				delete pFolder;
				continue;
			}
			/*
			* Register
			*/
			mSubFolders.Add(pFolder);
		}

		mValid = true;
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
	void DomainFolder::CreateFileFromSource(const String& sourceFilePath)
	{
		/*
		* First validate if the file exists
		*/
		if (!PlatformFile::IsExist(sourceFilePath))
		{
			LOG("DomainFile", "Invalid file path: {%s}", *sourceFilePath);
			return;
		}

		/*
		* Get extension
		*/
		const String extension = PlatformFile::GetExtension(sourceFilePath);

		/*
		* Check for asset importer
		*/
		const Array<Type*> types = Assembly::GetProcessAssembly()->GetTypes();
		Array<IAssetImporter*> foundImporters;
		Array<CustomAssetImporterAttribute*> foundImporterAttributes;
		for (unsigned int i = 0; i < types.GetCursor(); i++)
		{
			/*
			* Get and validate sub class
			*/
			Type* pType = types[i];

			if (!pType->IsSubClassOf(typeof(IAssetImporter)))
				continue;

			/*
			* Validate attribute
			*/
			CustomAssetImporterAttribute* pAttribute = pType->GetAttribute<CustomAssetImporterAttribute>();
			if (pAttribute == nullptr)
				continue;

			/*
			* Validate extensions
			*/
			const Array<String> extensions = pAttribute->GetExtensions();
			const int index = extensions.FindIndex(extension);
			if (index == -1)
				continue;

			foundImporterAttributes.Add(pAttribute);
			foundImporters.Add((IAssetImporter*)pType->CreateDefaultHeapObject());
		}

		/*
		* Check if there is a valid match for the requested file
		*/
		if (foundImporters.GetCursor() == 0) // return if there is no importers
		{
			LOG("DomainFolder", "Found no asset importers");
			return;
		}

		/*
		* Read the file
		*/
		ByteBlock fileContent;
		if (!PlatformFile::Read(sourceFilePath, fileContent))
		{
			LOG("DomainFolder", "Failed to load the file");
			return;
		}

		/*
		* Run import asset procedures
		*/
		for (unsigned int i = 0; i < foundImporters.GetCursor(); i++)
		{
			IAssetImporter* pFoundImporter = foundImporters[i];

			/*
			* Import
			*/
			pFoundImporter->OnImport(this,sourceFilePath);

			delete pFoundImporter;
		}
	}
	void DomainFolder::CreateResourceFile(const String& name, const String& type)
	{
		const String nameWithoutExtension = PlatformFile::GetNameWithoutExtension(name);
		const String sourceFilePath = mPath + "\\" + name;
		const String descriptorFilePath = mPath + "\\" + nameWithoutExtension + ".fd";

		/*
		* Validate if source file already exists
		*/
		if (PlatformFile::IsExist(sourceFilePath))
			return;

		/*
		* Validate if descriptor file already exists
		*/
		if (PlatformFile::IsExist(descriptorFilePath))
			return;

		/*
		* Create descriptor file
		*/
		DomainFileDescriptor fileDescriptor = {};
		fileDescriptor.ID = Guid::Create();
		fileDescriptor.SourceFile = name;
		fileDescriptor.ResourceType = type;

		const String fileDescriptorYAML = Yaml::ToYaml(&fileDescriptor);
		if (!PlatformFile::Create(descriptorFilePath))
		{
			LOG("DomainFolder", "Failed to create descriptor file");
			return;
		}
		if (!PlatformFile::Write(descriptorFilePath, fileDescriptorYAML))
		{
			LOG("DomainFolder", "Failed to write descriptor file for type %s", *type);
			return;
		}

		/*
		* Create default file
		*/
		ByteBlock defaultFileContent = {};
		if (!PlatformFile::Create(sourceFilePath))
		{
			LOG("DOmainFolder", "Failed to create default file");
			return;
		}
		if (!PlatformFile::Write(sourceFilePath, defaultFileContent))
		{
			LOG("DomainFolder", "Failed to write default file");
			return;
		}

		/*
		* Create file
		*/
		DomainFile* pFile = new DomainFile(descriptorFilePath,this);
		mFiles.Add(pFile);
	}
	void DomainFolder::CreateFileDescriptor(const String& name,const String& sourceFilePath, const String& resourceType)
	{
		const String path = mPath + "\\" + name + ".fd";

		if (!PlatformFile::Create(path))
		{
			LOG("DomainFolder", "Failed to create file descriptor");
			return;
		}

		DomainFileDescriptor fileDescriptor = {};
		fileDescriptor.ID = Guid::Create();
		fileDescriptor.SourceFile = sourceFilePath;
		fileDescriptor.ResourceType = resourceType;

		const String fileDescriptorYAML = Yaml::ToYaml(&fileDescriptor);

		if (!PlatformFile::Write(path, fileDescriptorYAML))
		{
			LOG("DomainFolder", "Failed to write file descriptor");
			return;
		}
	}
	void DomainFolder::DeleteFile(DomainFile* pFile)
	{
		/*
		* Validate if this file's parent folder
		*/
		if (!mFiles.Has(pFile))
			return;

		/*
		* Unload resource
		*/
		pFile->UnloadSync();

		/*
		* Delete physical files
		*/
		DeleteFilePhysical(pFile);

		mFiles.Remove(pFile);

		delete pFile;
	}
	void DomainFolder::Delete()
	{
		/*
		* First delete files
		*/
		for (unsigned int i = 0; i < mFiles.GetCursor(); i++)
		{
			DomainFile* pFile = mFiles[i];

			DeleteFile(pFile);

			i--;
		}
		mFiles.Clear();

		/*
		* Delete sub folders
		*/
		for (unsigned int i = 0; i < mSubFolders.GetCursor(); i++)
		{
			DeleteSubFolder(mSubFolders[i]);
			i--;
		}
		mSubFolders.Clear();

		
		/*
		* Remove this folder from the owner
		*/
		mParentFolder->DeleteSubFolder(this);
	}
	DomainFolder* DomainFolder::CreateFolder(const String& name)
	{
		/*
		* Validate folder name and path
		*/
		if (name == "")
			return nullptr;

		const String folderPath = mPath + "\\" + name;
		if (PlatformDirectory::IsDirectoryExist(folderPath))
		{
			LOG("DomainFolder", "Unable to create folder due to there is a folder with the same name");
			return nullptr;
		}

		/*
		* Create physical folder
		*/
		if (!PlatformDirectory::Create(folderPath))
		{
			LOG("DomainFolder", "Failed to create the folder");
			return nullptr;
		}

		/*
		* Create domain folder
		*/
		DomainFolder* pFolder = new DomainFolder(this,folderPath);
		mSubFolders.Add(pFolder);

		return pFolder;
	}
	void DomainFolder::DeleteSubFolder(DomainFolder* pFolder)
	{
		/*
		* Delete physical folders
		*/
		if (!PlatformDirectory::Delete(pFolder->GetFolderPath()))
		{
			LOG("DomainFolder", "Failed to delete the folder");
			return;
		}

		mSubFolders.Remove(pFolder);
		delete pFolder;
	}
	DomainFile* DomainFolder::RegisterFileViaDescriptor(const String& descriptorFilePath)
	{
		DomainFile* pFile = new DomainFile(descriptorFilePath, this);

		mFiles.Add(pFile);

		return pFile;
	}
	void DomainFolder::DeleteFilePhysical(DomainFile* pFile)
	{
		LOG("DomainFolder", "Deleting file: %s", *pFile->GetSourceFilePath());

		/*
		* Unload resource
		*/
		pFile->UnloadSync();

		/*
		* Delete physical files
		*/
		if (PlatformFile::IsExist(pFile->GetFileDescriptorPath()))
		{
			if (!PlatformFile::Delete(pFile->GetFileDescriptorPath()))
			{
				LOG("DomainFolder", "Failed to delete the file descriptor");
				return;
			}
		}
		
		if (PlatformFile::IsExist(pFile->GetSourceFilePath()))
		{
			if (!PlatformFile::Delete(pFile->GetSourceFilePath()))
			{
				LOG("DomainFolder", "Failed to delete the file source");
				return;
			}
		}
		else
		{

		}
	}
}