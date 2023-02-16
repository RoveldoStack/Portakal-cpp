#include "TextureAssetImporter.h"
#include <Runtime/Platform/PlatformFile.h>
#include <Editor/Domain/DomainFolder.h>
#include <Editor/Domain/DomainFile.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
	void TextureAssetImporter::OnImport(DomainFolder* pTargetFolder, const String& sourcePath)
	{
		/*
		* Create text file descriptor
		*/
		const String name = PlatformFile::GetNameWithoutExtension(sourcePath);
		const String targetPath = pTargetFolder->GetFolderPath() + "\\" + PlatformFile::GetName(sourcePath);
		const String descriptorPath = pTargetFolder->GetFolderPath() + "\\" + name + ".fd";
		pTargetFolder->CreateFileDescriptor(name, PlatformFile::GetName(targetPath), "texture");

		/*
		* Copy
		*/
		if (!PlatformFile::Copy(targetPath, sourcePath))
		{
			LOG("TextureAssetImporter", "Failed to copy the texture");
			return;
		}

		/*
		* Register immediate
		*/
		pTargetFolder->RegisterFileViaDescriptor(descriptorPath);
	}
}