#include "GarbageCollector.h"

namespace Portakal
{
	GarbageCollector* GarbageCollector::sCollector = nullptr;

	void GarbageCollector::Initialize()
	{
		sCollector = new GarbageCollector();
	}

	unsigned long long GarbageCollector::GetMemory()
	{
		if (sCollector == nullptr)
			return 0;

		return sCollector->mSize;
	}

	void GarbageCollector::Collect()
	{
		if (sCollector == nullptr)
			return;

		sCollector->mCriticalSection->Lock();

		for (unsigned int i = 0; i < sCollector->mObjects.GetCursor(); i++)
		{
			delete sCollector->mObjects[i];
		}
		sCollector->mObjects.Clear();
		sCollector->mSize = 0;

		sCollector->mCriticalSection->Release();
	}

	void GarbageCollector::_Register(TaggedObject* pObject)
	{
		if (sCollector == nullptr)
			return;

		sCollector->mCriticalSection->Lock();

		sCollector->mObjects.Add(pObject);
		sCollector->mSize += pObject->GetType()->GetSize();

		sCollector->mCriticalSection->Release();
	}

	GarbageCollector::GarbageCollector()
	{
		mCriticalSection = PlatformCriticalSection::Create();
		mSize = 0;
	}

	GarbageCollector::~GarbageCollector()
	{

	}

}