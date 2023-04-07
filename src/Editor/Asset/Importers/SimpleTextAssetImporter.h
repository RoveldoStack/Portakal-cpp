#pragma once
#include <Editor/Asset/IAssetImporter.h>
#include <Editor/Asset/CustomAssetImporterAttribute.h>

namespace Portakal
{
	class DomainFile;
	CLASS_ATTRIBUTE(CustomAssetImporterAttribute, "simple_text", { ".txt",".docx" });
	class PORTAKAL_API SimpleTextAssetImporter : public IAssetImporter
	{
		GENERATE_CLASS(SimpleTextAssetImporter);
	public:
		SimpleTextAssetImporter() = default;
		~SimpleTextAssetImporter() = default;

		virtual void OnImport(DomainFolder* pTargetFolder,const String& sourcePath) override;
	};

	/*START_GENERATE_TYPE(SimpleTextAssetImporter);
	START_TYPE_PROPERTIES(SimpleTextAssetImporter);
	REGISTER_BASE_TYPE(IAssetImporter);
	REGISTER_TYPE_ATTRIBUTE(CustomAssetImporterAttribute, "simple_text", { ".txt",".docx" });
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(SimpleTextAssetImporter);
	END_GENERATE_TYPE(SimpleTextAssetImporter);*/

#include "SimpleTextAssetImporter.reflect.h"
}