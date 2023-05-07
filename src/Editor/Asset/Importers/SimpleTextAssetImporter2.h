#pragma once
#include <Editor/Asset/IAssetImporter.h>
#include <Editor/Asset/CustomAssetImporterAttribute.h>

namespace Portakal
{
	class DomainFile;
	PCLASS_ATTRIBUTE(CustomAssetImporterAttribute, "simple_text", { ".txt",".docx" });
	PCLASS();
	class PORTAKAL_API SimpleTextAssetImporter2 : public IAssetImporter
	{
		GENERATE_CLASS(SimpleTextAssetImporter2);
	public:
		SimpleTextAssetImporter2() = default;
		~SimpleTextAssetImporter2() = default;

		virtual void OnImport(DomainFolder* pTargetFolder, const String& sourcePath) override;
	};


#include "SimpleTextAssetImporter2.reflect.h"
}