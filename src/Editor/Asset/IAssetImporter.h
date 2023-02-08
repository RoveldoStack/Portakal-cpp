#pragma once
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Memory/ByteBlock.h>
namespace Portakal
{
	class DomainFolder;
	class PORTAKAL_API IAssetImporter : public Class
	{
		GENERATE_CLASS(IAssetImporter);
	public:
		IAssetImporter() = default;
		~IAssetImporter() = default;

		virtual void OnImport(DomainFolder* pTargetFolder,const String& targetPath,const ByteBlock& dataBlock) = 0;
	};

	START_GENERATE_TYPE(IAssetImporter);
	START_TYPE_PROPERTIES(IAssetImporter);
	END_TYPE_PROPERTIES;
	VIRTUAL_TYPE;
	END_GENERATE_TYPE(IAssetImporter);
}