#include "DomainFolder.h"
#include <Runtime/Platform/PlatformDirectory.h>
#include <Runtime/Log/Log.h>
#include <Runtime/Platform/PlatformMessage.h>
#include <Editor/Domain/DomainFileDescriptorYamlSerialize.h>
#include <Runtime/Yaml/Yaml.h>
#include <Runtime/Platform/PlatformFile.h>
#include <Editor/Asset/IAssetSerializer.h>
#include <Editor/Asset/CustomAssetSerializerAttribute.h>
#include <Editor/Domain/DomainFile.h>
#include <Editor/Asset/CustomAssetImporterAttribute.h>
#include <Editor/Asset/IAssetImporter.h>
#include <Editor/Asset/SimpleTextAssetImporter.h>
#include <Editor/Asset/SimpleTextAssetImporter2.h>
#include <Editor/Domain/DomainFileDescriptorYamlSerialize.h>
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
			const String sourceFilePath = path + "\\";
			DomainFile* pFile = new DomainFile(filePath, this);

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
			LOG("DomainFOlder", "Failed to write file descriptor");
			return;
		}

	}
	void DomainFolder::CreateFolder(const String& name)
	{
		/*
		* Validate folder name and path
		*/
		if (name == "")
			return;
		const String folderPath = mPath + "\\" + name;
		if (PlatformDirectory::IsDirectoryExist(folderPath))
		{
			LOG("DomainFolder", "Unable to create folder due to there is a folder with the same name");
			return;
		}

		/*
		* Create physical folder
		*/
		if (!PlatformDirectory::Create(folderPath))
		{
			LOG("DomainFolder", "Failed to create the folder");
			return;
		}

		/*
		* Create domain folder
		*/
		DomainFolder* pFolder = new DomainFolder(this,folderPath);
		mSubFolders.Add(pFolder);
	}
	DomainFile* DomainFolder::RegisterFileViaDescriptor(const String& descriptorFilePath)
	{
		DomainFile* pFile = new DomainFile(descriptorFilePath, this);

		mFiles.Add(pFile);

		return pFile;
	}
}