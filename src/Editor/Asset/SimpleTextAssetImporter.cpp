#include "SimpleTextAssetImporter.h"
#include <Runtime/Log/Log.h>
#include <Runtime/Platform/PlatformFile.h>

namespace Portakal
{
	void SimpleTextAssetImporter::OnImport(DomainFolder* pTargetFolder,const String& targetPath, const ByteBlock& dataBlock)
	{
		String context((const char*)dataBlock.GetBlockDataPtr(),dataBlock.GetBlockSizeInBytes());
		context += "Zaaaa";
		PlatformFile::Write(targetPath, context);
	}
}