#pragma once
#include <Editor/Asset/IAssetImporter.h>
#include <Editor/Asset/CustomAssetImporterAttribute.h>

namespace Portakal
{
	class DomainFile;
	PCLASS_ATTRIBUTE(CustomAssetImporterAttribute, "texture", { ".png",".jpg",".jpeg" });
	PCLASS();
	class PORTAKAL_API TextureAssetImporter : public IAssetImporter
	{
		GENERATE_CLASS(TextureAssetImporter);
	public:
		TextureAssetImporter() = default;
		~TextureAssetImporter() = default;

		virtual void OnImport(DomainFolder* pTargetFolder, const String& sourcePath) override;
	private:
	};

#include "TextureAssetImporter.reflect.h"

}