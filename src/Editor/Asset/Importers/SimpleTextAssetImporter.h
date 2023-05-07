#pragma once
#include <Editor/Asset/IAssetImporter.h>
#include <Editor/Asset/CustomAssetImporterAttribute.h>

namespace Portakal
{
	class DomainFile;
	PCLASS_ATTRIBUTE(CustomAssetImporterAttribute, "simple_text", { ".txt",".docx" });
	PCLASS();
	class PORTAKAL_API SimpleTextAssetImporter : public IAssetImporter
	{
		GENERATE_CLASS(SimpleTextAssetImporter);
	public:
		SimpleTextAssetImporter() = default;
		~SimpleTextAssetImporter() = default;

		virtual void OnImport(DomainFolder* pTargetFolder,const String& sourcePath) override;
	};

#include "SimpleTextAssetImporter.reflect.h"
}