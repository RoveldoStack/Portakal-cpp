#pragma once
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Memory/ByteBlock.h>
namespace Portakal
{
	class DomainFolder;
	class DomainFile;
	class PORTAKAL_API IAssetImporter : public Class
	{
		GENERATE_CLASS(IAssetImporter,Virtual);
	public:
		IAssetImporter() = default;
		~IAssetImporter() = default;

		virtual void OnImport(DomainFolder* pTargetFolder,const String& sourcePath) = 0;
	};

	//START_GENERATE_TYPE(IAssetImporter);
	//START_TYPE_PROPERTIES(IAssetImporter);
	//END_TYPE_PROPERTIES;
	//NO_DEFAULT_CONSTRUCTOR;
	//END_GENERATE_TYPE(IAssetImporter);

#include "IAssetImporter.reflect.h"
}