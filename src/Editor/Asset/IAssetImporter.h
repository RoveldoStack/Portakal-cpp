#pragma once
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Memory/ByteBlock.h>
namespace Portakal
{
	class DomainFolder;
	class DomainFile;
	PCLASS();
	class PORTAKAL_API IAssetImporter : public Class
	{
		GENERATE_CLASS(IAssetImporter,Virtual);
	public:
		IAssetImporter() = default;
		~IAssetImporter() = default;

		virtual void OnImport(DomainFolder* pTargetFolder,const String& sourcePath) = 0;
	};
#include "IAssetImporter.reflect.h"
}