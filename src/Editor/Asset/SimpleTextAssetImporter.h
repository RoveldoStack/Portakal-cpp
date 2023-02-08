#pragma once
#include <Editor/Asset/IAssetImporter.h>
#include <Editor/Asset/CustomAssetImporterAttribute.h>

namespace Portakal
{
	class PORTAKAL_API SimpleTextAssetImporter : public IAssetImporter
	{
		GENERATE_CLASS(SimpleTextAssetImporter);
	public:
		SimpleTextAssetImporter() = default;
		~SimpleTextAssetImporter() = default;

		virtual void OnImport(DomainFolder* pTargetFolder,const String& targetPath, const ByteBlock& dataBlock) override;
	};

	START_GENERATE_TYPE(SimpleTextAssetImporter);
	START_TYPE_PROPERTIES(SimpleTextAssetImporter);
	REGISTER_BASE_TYPE(IAssetImporter);
	REGISTER_TYPE_ATTRIBUTE(CustomAssetImporterAttribute, "simple_text", { ".txt",".docx" });
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(SimpleTextAssetImporter);
	END_GENERATE_TYPE(SimpleTextAssetImporter);
}