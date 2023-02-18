#pragma once
#include <Editor/Asset/IAssetImporter.h>
#include <Editor/Asset/CustomAssetImporterAttribute.h>

namespace Portakal
{
	class DomainFile;
	class PORTAKAL_API SimpleTextAssetImporter2 : public IAssetImporter
	{
		GENERATE_CLASS(SimpleTextAssetImporter2);
	public:
		SimpleTextAssetImporter2() = default;
		~SimpleTextAssetImporter2() = default;

		virtual void OnImport(DomainFolder* pTargetFolder, const String& sourcePath) override;
	};

	START_GENERATE_TYPE(SimpleTextAssetImporter2);
	START_TYPE_PROPERTIES(SimpleTextAssetImporter2);
	REGISTER_BASE_TYPE(IAssetImporter);
	REGISTER_TYPE_ATTRIBUTE(CustomAssetImporterAttribute, "simple_text", { ".txt",".docx" });
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(SimpleTextAssetImporter2);
	END_GENERATE_TYPE(SimpleTextAssetImporter2);
}