#pragma once
#include <Editor/Asset/IAssetImporter.h>
#include <Editor/Asset/CustomAssetImporterAttribute.h>

namespace Portakal
{
	class DomainFile;
	class PORTAKAL_API TextureAssetImporter : public IAssetImporter
	{
		GENERATE_CLASS(TextureAssetImporter);
	public:
		TextureAssetImporter() = default;
		~TextureAssetImporter() = default;

		virtual void OnImport(DomainFolder* pTargetFolder, const String& sourcePath) override;
	private:
	};

	START_GENERATE_TYPE(TextureAssetImporter);
	START_TYPE_PROPERTIES(TextureAssetImporter);
	REGISTER_BASE_TYPE(IAssetImporter);
	REGISTER_TYPE_ATTRIBUTE(CustomAssetImporterAttribute, "texture", { ".png",".jpg",".jpeg" });
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(TextureAssetImporter);
	END_GENERATE_TYPE(TextureAssetImporter);

}