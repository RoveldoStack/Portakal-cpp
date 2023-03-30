#include "ResourceLoadJob.h"
#include <Runtime/Memory/ByteBlock.h>
#include <Runtime/Platform/PlatformFile.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Resource/IResourceSerializer.h>
namespace Portakal
{
	ResourceLoadJob::ResourceLoadJob(IResourceSerializer* pSerializer, const String& filePath, const unsigned long long offset, const unsigned long long size,const Delegate<void,ResourceSubObject*>& signal) 
		: mFilePath(filePath)
		, mOffset(offset)
		, mSize(size)
		, mSerializer(pSerializer)
		, mSignalDelegate(signal)
	{

	}
	ResourceLoadJob::~ResourceLoadJob()
	{
		mSerializer = nullptr;
	}
	void ResourceLoadJob::Run()
	{
		LOG("Filepath", ":%s", *PlatformFile::GetNameWithoutExtension(mFilePath));
		if (PlatformFile::GetNameWithoutExtension(mFilePath) == "smiley")
		{
			LOG("hey", "hey");
		}
		ByteBlock tempBlock = {};
		ASSERT(PlatformFile::Read(mFilePath, tempBlock, mOffset, mOffset + mSize), "Resource", "Failed to load the file");
		ResourceSubObject* pObject = mSerializer->Deserialize(tempBlock);

		mSignalDelegate.Invoke(pObject);
	}
}