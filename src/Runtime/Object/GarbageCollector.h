#pragma
#include <Runtime/Object/TaggedObject.h>
#include <Runtime/Object/API.h>
#include <Runtime/Platform/PlatformCriticalSection.h>

namespace Portakal
{
	class PORTAKAL_API GarbageCollector
	{
		friend class TaggedObject;
	private:
		static GarbageCollector* sCollector;
	public:
		static void Initialize();
		static unsigned long long GetMemory();
		static void Collect();
	private:
		static void _Register(TaggedObject* pObject);
	private:
		GarbageCollector();
		~GarbageCollector();
	private:
		Array<TaggedObject*> mObjects;
		PlatformCriticalSection* mCriticalSection;
		unsigned long long mSize;
	};
}