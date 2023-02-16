#include "SimpleTextAssetImporter2.h"
#include <Runtime/Log/Log.h>
#include <Runtime/Platform/PlatformFile.h>
#include <Editor/Domain/DomainFolder.h>
#include <Editor/Domain/DomainFile.h>

namespace Portakal
{

	void SimpleTextAssetImporter2::OnImport(DomainFolder* pTargetFolder, const String& sourcePath)
	{
		/*
		* Create text file descriptor
		*/
		const String name = PlatformFile::GetNameWithoutExtension(sourcePath) + "2";
		const String targetPath = pTargetFolder->GetFolderPath() + "\\" + name + ".txt";
		const String descriptorPath = pTargetFolder->GetFolderPath() + "\\" + name + ".fd";
		pTargetFolder->CreateFileDescriptor(name, PlatformFile::GetName(targetPath), "simple-text");

		/*
		* Read text content
		*/
		String content;
		if (!PlatformFile::Read(sourcePath, content))
		{
			LOG("SimpleTextAssetImporter", "Failed read the simple text");
		}
		content += "SEXX";

		/*
		* Write the text content
		*/
		PlatformFile::Create(targetPath);
		PlatformFile::Write(targetPath, *content);

		/*
		* Create via descriptor file
		*/
		pTargetFolder->RegisterFileViaDescriptor(descriptorPath);
	}

}